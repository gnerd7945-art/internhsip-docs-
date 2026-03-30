#include<gst/gst.h> 
#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

// Use an atomic bool so both threads can see when to stop safely
std::atomic<bool> keep_running(true);

// 1. THE BUS CALLBACK (The "Emergency Protocol")
// This runs in the BACKGROUND thread managed by GMainLoop
 gboolean bus_call(GstBus *bus, GstMessage *msg, gpointer data) {
    GMainLoop *loop = (GMainLoop *)data;

    switch (GST_MESSAGE_TYPE(msg)) {
        case GST_MESSAGE_EOS:
            std::cout << "\n[Bus] End of stream reached." << std::endl;
            keep_running = false;
            g_main_loop_quit(loop);
            break;

        case GST_MESSAGE_ERROR: {
            gchar *debug;
            GError *error;
            // "Unboxing" the message suitcase
            gst_message_parse_error(msg, &error, &debug);
            
            std::cerr << "\n[Bus] CRITICAL ERROR: " << error->message << std::endl;
            if (debug) std::cerr << "[Bus] Debug Info: " << debug << std::endl;

            g_error_free(error); // Cleaning the "House"
            g_free(debug);      // Cleaning the debug string
            
            keep_running = false;
            g_main_loop_quit(loop);
            break;
        }
        default:
            break;
    }
    return TRUE; // Keep listening for more messages
}

// 2. THE THREAD FUNCTION
void run_glib_loop(GMainLoop* loop) {
    g_main_loop_run(loop);
    std::cout << "[Thread] GMainLoop has exited." << std::endl;
}

int main(int argc, char *argv[]) {  
    // Initialize GStreamer
    gst_init(&argc, &argv);

    // --- CONSTRUCTION PHASE ---
    
    // Create the Master Container (The Factory Floor)
    GstElement *pipeline = gst_pipeline_new("cv-pipeline");

    // Create Elements (The Blueprints -> The Workers)
    GstElement *source  = gst_element_factory_make("v4l2src", "camera-source");
    GstElement *filter  = gst_element_factory_make("videoconvert", "converter");
    GstElement *sink    = gst_element_factory_make("appsink", "cv-sink");

    if (!pipeline || !source || !filter || !sink) {
        std::cerr << "Failed to create elements. Check if plugins are installed." << std::endl;
        return -1;
    }

    // --- CONFIGURATION PHASE ---

    // Set properties using the Key-Value system
    // "device" is the key, "/dev/video0" is the value
    g_object_set(G_OBJECT(source), "device", "/dev/video0", NULL);

    // Configure appsink for CV performance
    g_object_set(G_OBJECT(sink), 
                 "emit-signals", TRUE, 
                 "sync", FALSE, 
                 "drop", TRUE, 
                 "max-buffers", 1, 
                 NULL);

    // --- ASSEMBLY PHASE ---

    // Add elements to the pipeline (Box in a Box)
    // We cast pipeline to GST_BIN because add_many belongs to the Bin class
    gst_bin_add_many(GST_BIN(pipeline), source, filter, sink, NULL);

    // Connect the Pads (The actual pipes)
    if (!gst_element_link_many(source, filter, sink, NULL)) {
        std::cerr << "Elements could not be linked!" << std::endl;
        gst_object_unref(pipeline);
        return -1;
    }

    // --- COMMUNICATION PHASE ---

    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    GstBus *bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
    
    // Attach the bus watcher to the loop
    gst_bus_add_watch(bus, (GstBusFunc)bus_call, loop);
    gst_object_unref(bus); // The watch now "owns" a reference

    // --- EXECUTION PHASE ---

    std::cout << "Starting pipeline..." << std::endl;
    gst_element_set_state(pipeline, GST_STATE_PLAYING);

    // Spin off the Management Thread
    std::thread gst_manager_thread(run_glib_loop, loop); //gst_manage_thread is thread object of thread class, could have written t

    // --- DECOUPLED MAIN WORK LOOP ---
    std::cout << "Main C++ thread is now free for AI work!" << std::endl;
    
    int frame_count = 0;
    while (keep_running) {
        // This is where your OpenCV/TensorRT/AI code would live.
        // It is NOT blocked by GStreamer's internal workings.
        std::cout << "\r[Main Thread] Processing AI Frame: " << frame_count++ << std::flush;
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        // Example: Stop after 50 iterations for testing
        if (frame_count > 50) {
            std::cout << "\n[Main Thread] Work finished. Stopping..." << std::endl;
            g_main_loop_quit(loop);
            break;
        }
    }

    // --- CLEANUP PHASE ---

    std::cout << "Cleaning up..." << std::endl;
    gst_element_set_state(pipeline, GST_STATE_NULL);
    
    // Wait for the background thread to finish
    if (gst_manager_thread.joinable()) {
        gst_manager_thread.join();
    }

    // Free the big objects (The workers)
    // Note: unreffing the pipeline automatically unrefs everything inside it
    gst_object_unref(pipeline);
    g_main_loop_unref(loop);

    std::cout << "Done." << std::endl;
    return 0;
}
