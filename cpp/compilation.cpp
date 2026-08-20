1) OBJECT file-> Header files contain DECLERATION, and the compiler uses them to validate if a function in the .cpp file follows the correct declaration. 
  It ultimately creates an object file combining the .cpp and header files.
2) I flag -> affress of header files are added using I flag. 
    EXAMPLE: 
            When the compiler sees #include <filename.h>, it searches for this file in the paths specified by the -I flags. After this, it goes on to search in:

           -> CPLUS_INCLUDE_PATH (for C++ files)
        
           -> C_INCLUDE_PATH (for C files)
        
           -> CPATH (for both)
        
            -> If still not found, it searches the compiler's built-in standard system directories (e.g., /usr/include, /usr/local/include).

    The object file after this contains the mangled name of the function. The mangled name is a mix of the namespace, nested level, and function signature.

3) LINKING and MACHINE BINARY -> Now that we have the object file, the -L and -l flags come into play. The -l flag contains the library name(.so filename) that has
  the DEFINATION, and the -L flag has the path to it. If the -L flag is missing, the linker searches for this systematically in its default directories.   THIS ALL HAPPENS IN COMPILE TIME.

   -> The linker does not actually add the implementation/definition into the binary; it only adds symbols and references( a way to verify that defination exist) . After this step, we get a machine-level binary.
  
4) LOADER ->  The loader is actually used at runtime to connect instructions( definations)  by loading the .so file from the disk into RAM and providing a pointer to it for all those file using
    this specific .so file. THIS ALL HAPPENS IN RUNTIME.

   -> LD_LIBRARY_PATH and the default system paths are used to search for .so files because the binary actually only contains the filename (from the -l flag) and not its path.
      Basically LD_LIBRARY_PATH plays the same role as L flag to search .so files mentioned in -l flag

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
I)hy does the linker just add references? Why not fetch the complete code?...why wait for loader step? What this linker step actually do in binary?"

When you link against a STATIC LIBRARY (a .a file instead of a .so file), the linker goes to the path, grabs the exact machine instructions (definitions), and physically copies them inside your final binary.
There is no loader step required at runtime for those functions.

So, why do we use dynamic linking (.so files) and wait for the loader? TO SAVE disk space, RAM, and allow for easy updates.

Imagine if every single program on your computer (browser, text editor, terminal) physically copied the instructions for printf into its own binary.

    Disk Bloat: Your hard drive would contain thousands of identical copies of the printf code.

    RAM Waste: When you run 10 programs, RAM would load 10 separate copies of printf.

    Security/Updates: If a security bug is found in printf, you would have to recompile every single app on your computer.

By using Dynamic Linking (Shared Objects / .so), we only keep one copy of the library on the hard drive. When you run 10 programs, the OS loads that .so file into RAM once, and all 10 programs share it.
 LINKER DOES:-
    1) Verification: It goes to the -L path, opens the .so file, and checks: "Does the calculate() function actually exist in here? Is the mangled name correct?" If yes, the linker says:- 
                  "Okay, the code exists, I will allow the build to succeed."

    2)  Writing the "Promissory Note": It adds a dynamic dependency tag (called DT_NEEDED) inside your executable. It literally writes a string into your binary that says:- 
        "I need libmath.so to run." (Notice it usually does not save the absolute path from -L, which keeps your binary portable so you can give it to a friend whose paths might be different).

    3)  Building the Jump Table: It creates an empty routing table in your binary called the PLT/GOT (Procedure Linkage Table / Global Offset Table). It leaves empty slots in this table.
        The GOT (Global Offset Table) is literally just an array of pointers that hold the actual RAM addresses of the functions in .so files after the .so file is loaded into memory by the operating system.

Later, at Runtime:
When you execute the program, the Loader reads that "promissory note." It searches your computer (using LD_LIBRARY_PATH and system paths) to find libmath.so.
loader  loads the library into RAM, finds the exact memory address of calculate(), and fills in that empty slot in the PLT/GOT table. Now, when your program calls calculate(), 
it seamlessly jumps to the shared library in RAM.



II)  When an ABI (Application Binary Interface) mismatch occurs, not finding the mangled name in the symbol table is the most common and immediate symptom.

1. Build-Time ABI Mismatch (The Linker Fails)

This happens when you compile your code.

    The Setup: Your -I flag points to Boost 1.85 headers. The compiler generates an object file (.o) asking for a specific Boost 1.85 mangled name (e.g., _ZN5boost4json5value1_85_0).

    The Mismatch: Your -l flag tells the linker to find the library, but without the correct -L path, the linker grabs the default system Boost 1.74 .so file.

    The Result: The linker checks the 1.74 symbol table, doesn't find the 1.85 mangled name, and throws a massive undefined reference error. The build completely stops, and no executable is created.

2. Run-Time ABI Mismatch (The Loader Crashes)

This happens when your program built successfully, but fails when you try to run it.

    The Setup: You built the program correctly using the perfect -L path. The executable (./Monitor) successfully saved the mangled name and the required library filename (libboost_json.so).

    The Mismatch: You type ./Monitor to run it. The dynamic loader (ld-linux.so) uses standard system paths or LD_LIBRARY_PATH to find the .so file. However, it accidentally finds a different version of libboost_json.so on your disk than the one you compiled against.

    The Result: The loader opens the wrong .so, scans the symbol table, and fails to find the mangled name. The program immediately crashes with an undefined symbol or symbol lookup error.

3. The Silent Killer: When Mangled Names Do Match

There is one more type of ABI mismatch that is much harder to debug—this is what happened with your DeepStream TensorRT crash.
    
    Sometimes, a function's mangled name stays exactly the same between version 1.0 and 2.0 of a library, so the linker and loader both find it in the symbol table perfectly.
    
    However, the internal memory layout changed.
    For example, in Version 1.0, a Person object took up 16 bytes of RAM. In Version 2.0, the developers added a new variable, so the Person object now takes up 24 bytes of RAM.
    
    If you compile your code with the Version 1.0 headers, your program allocates 16 bytes. But if the loader connects it to the Version 2.0 .so file at runtime, the library tries to write 24 bytes of data into a 16-byte space.
    
    The symbol table said everything was fine, but the memory overflow destroys the data. The OS detects this illegal memory write and instantly kills the program, giving you a Segmentation fault (core dumped).

