# =====================================================
# BUILD STAGE
# =====================================================

FROM deepstream-buildenv:1.0 AS build

WORKDIR /opt

# -----------------------------------------------------
# Packages required during build
# -----------------------------------------------------

# Disable the broken Intel RealSense repository
RUN rm -f /etc/apt/sources.list.d/archive_uri-https_librealsense_intel_com_debian_apt-repo-jammy.list

# Install build dependencies
RUN apt-get update && \
    apt-get install -y \
        wget \
        bzip2 \
        sqlite3 \
        python3-pip \
        libusb-0.1-4 \
        libusb-dev \
        libexif-dev && \
    rm -rf /var/lib/apt/lists/*

# -----------------------------------------------------
# Download & Build Boost 1.85
# -----------------------------------------------------

WORKDIR /tmp
# Purge existing OpenCV versions to prevent conflicts
RUN apt-get remove -y "libopencv*" || true && \
    rm -rf \
        /usr/local/include/opencv4 \
        /usr/local/lib/libopencv* \
        /usr/include/opencv4 \
        /usr/lib/x86_64-linux-gnu/libopencv*

# Download & build OpenCV 4.5.5
RUN wget -O opencv-4.5.5.tar.gz \
        https://github.com/opencv/opencv/archive/4.5.5.tar.gz && \
    tar -xzf opencv-4.5.5.tar.gz && \
    rm opencv-4.5.5.tar.gz && \
    mkdir -p opencv-4.5.5/build && \
    cd opencv-4.5.5/build && \
    cmake \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=/usr/local \
        -DBUILD_SHARED_LIBS=ON \
        -DBUILD_TESTS=OFF \
        -DBUILD_PERF_TESTS=OFF \
        -DBUILD_EXAMPLES=OFF \
        -DWITH_FFMPEG=ON \
        -DWITH_GSTREAMER=ON \
        .. && \
    cmake --build . -j"$(nproc)" && \
    cmake --install . && \
    cd /tmp && \
    rm -rf opencv-4.5.5


# Purge old Boost versions to prevent conflicts
RUN apt-get remove -y "libboost*-dev" || true && \
    rm -rf /usr/local/include/boost \
           /usr/local/lib/libboost* \
           /usr/include/boost \
           /usr/lib/x86_64-linux-gnu/libboost*

RUN wget -O boost_1_85_0.tar.bz2 \
        https://archives.boost.io/release/1.85.0/source/boost_1_85_0.tar.bz2 && \
    tar -xjf boost_1_85_0.tar.bz2 && \
    rm boost_1_85_0.tar.bz2 && \
    cd boost_1_85_0 && \
    ./bootstrap.sh && \
    ./b2 install \
        --with-json \
        --with-system \
        --prefix=/usr/local \
        -j"$(nproc)" && \
    cd /tmp && \
    rm -rf boost_1_85_0

 # Purge old GStreamer RTSP Server files to prevent conflicts

RUN apt-get remove -y "libgstrtspserver*" || true && \

    rm -rf /usr/include/gstreamer-1.0/gst/rtsp-server \

           /usr/lib/x86_64-linux-gnu/libgstrtspserver* \

           /usr/local/lib/libgstrtspserver* \

           /usr/local/include/gstreamer-1.0/gst/rtsp-server



RUN apt-get update && apt-get install -y \

    libgstrtspserver-1.0-dev \

    && rm -rf /var/lib/apt/lists/* 


# -----------------------------------------------------
# Project files
# -----------------------------------------------------

COPY sfe_toolkits/                 /opt/sfe_toolkits/
COPY mikshi_box/common/            /opt/mikshi_box/common/
COPY mikshi_box/libs/              /opt/mikshi_box/libs/
COPY mikshi_box/source/            /opt/mikshi_box/source/
COPY mikshi_box/scripts/           /opt/mikshi_box/scripts/
COPY mikshi_box/utilities/         /opt/mikshi_box/utilities/

RUN chmod +x /opt/mikshi_box/scripts/*.sh

RUN rm -rf \
    /opt/mikshi_box/source/build-debug \
    /opt/mikshi_box/source/build-release

# -----------------------------------------------------
# Configure
# -----------------------------------------------------

ENV LD_LIBRARY_PATH=/usr/local/cuda-12.6/compat/lib.real:$LD_LIBRARY_PATH

WORKDIR /opt/mikshi_box/source

RUN cmake \
        --preset debug \
        -DSFE_TOOLKIT_PATH=/opt/sfe_toolkits \
        -DCMAKE_C_FLAGS="-w" \
        -DCMAKE_CXX_FLAGS="-w"
        


# -----------------------------------------------------
# Build (verbose)
# -----------------------------------------------------

RUN cmake --build --preset debug -- VERBOSE=1

# -----------------------------------------------------
# Verify every executable links to Boost 1.85
# -----------------------------------------------------
RUN echo "==================================================" && \
    echo "Binary dependencies" && \
    echo "==================================================" && \
    for f in /opt/mikshi_box/bin/*; do \
        if [ -f "$f" ] && [ -x "$f" ]; then \
            echo; \
            echo "========== $(basename "$f") =========="; \
            readelf -d "$f" | grep -E "NEEDED|RUNPATH|RPATH" || true; \
            ldd "$f" | grep boost || true; \
            ldd "$f" | grep opencv || true; \
        fi; \
    done


# -----------------------------------------------------
# Strip binaries
# -----------------------------------------------------

RUN strip /opt/mikshi_box/bin/* || true

# Runtime configuration (changes frequently)
COPY mikshi_box/data/                        /opt/mikshi_box/data/


# =====================================================
# RUNTIME STAGE
# =====================================================

FROM nvcr.io/nvidia/deepstream:7.1-gc-triton-devel
RUN rm -f /etc/apt/sources.list.d/archive_uri-https_librealsense_intel_com_debian_apt-repo-jammy.list

# -----------------------------------------------------
# Runtime packages
# -----------------------------------------------------
 #1 sqlite,python , micro ..
RUN apt-get update && \
    apt-get install -y \
        sqlite3 \
        sqlitebrowser \
        gettext-base \
        python3-pip \
        wget \
        micro && \
    rm -rf /var/lib/apt/lists/*

#2 gst rtsp server .so files 
RUN apt-get update && apt-get install -y \
    libgstrtspserver-1.0-0 \
    && rm -rf /var/lib/apt/lists/*


# Install runtime python dependencies that were missing
RUN python3 -m pip install --no-cache-dir psutil requests
# -----------------------------------------------------
# TensorRT 10.9.0.34
# -----------------------------------------------------

COPY nv-tensorrt-local-repo-ubuntu2204-10.9.0-cuda-12.8_1.0-1_amd64.deb /tmp/

RUN dpkg -i /tmp/nv-tensorrt-local-repo-ubuntu2204-10.9.0-cuda-12.8_1.0-1_amd64.deb && \
    cp /var/nv-tensorrt-local-repo-ubuntu2204-10.9.0-cuda-12.8/nv-tensorrt-local-*-keyring.gpg \
       /usr/share/keyrings/ && \
    \
    # Temporarily disable NVIDIA online CUDA repository
    mkdir -p /tmp/disabled-apt-sources && \
    mv /etc/apt/sources.list.d/cuda*.list \
       /tmp/disabled-apt-sources/ 2>/dev/null || true && \
    mv /etc/apt/sources.list.d/nvidia*.list \
       /tmp/disabled-apt-sources/ 2>/dev/null || true && \
    \
    apt-get update && \
    \
    echo "===== TensorRT candidate =====" && \
    apt-cache policy libnvinfer10 && \
    \
    apt-get install -y --no-install-recommends \
        libnvinfer10=10.9.0.34-1+cuda12.8 \
        libnvinfer-plugin10=10.9.0.34-1+cuda12.8 \
        libnvonnxparsers10=10.9.0.34-1+cuda12.8 \
        libnvinfer-bin=10.9.0.34-1+cuda12.8 \
        libnvinfer-dev=10.9.0.34-1+cuda12.8 && \
    \
    apt-mark hold \
        libnvinfer10 \
        libnvinfer-plugin10 \
        libnvonnxparsers10 \
        libnvinfer-bin \
        libnvinfer-dev && \
    \
    echo "===== Installed TensorRT =====" && \
    dpkg-query -W -f='${Package} ${Version}\n' \
        libnvinfer10 \
        libnvinfer-plugin10 \
        libnvonnxparsers10 \
        libnvinfer-bin \
        libnvinfer-dev && \
    \
    # Restore NVIDIA online repositories
    mv /tmp/disabled-apt-sources/*.list \
       /etc/apt/sources.list.d/ 2>/dev/null || true && \
    \
    rm -rf \
        /tmp/nv-tensorrt-local-repo-*.deb \
        /tmp/disabled-apt-sources \
        /var/lib/apt/lists/*

WORKDIR /opt/mikshi_box

# -----------------------------------------------------
# Runtime directories
# -----------------------------------------------------

RUN mkdir -p \
    /opt/mikshi_box/comm \
    /opt/mikshi_box/logs \
    /opt/mikshi_box/runtime/newfaces \
    /opt/mikshi_box/runtime/ProcessedImg \
    /opt/mikshi_box/runtime/ProcessedUnregisteredImg \
    /opt/mikshi_box/runtime/records_storage

# -----------------------------------------------------
# Application
# -----------------------------------------------------

COPY --from=build /opt/mikshi_box/bin ./bin

COPY --from=build /opt/mikshi_box/libs ./libs

# -----------------------------------------------------
# Runtime libraries
# -----------------------------------------------------

COPY --from=build /usr/local/lib/libopencv*.so* \
                  /usr/local/lib/

COPY --from=build /usr/lib/x86_64-linux-gnu/libtbb.so* \
                  /usr/lib/x86_64-linux-gnu/

COPY --from=build /usr/lib/x86_64-linux-gnu/libusb-0.1.so.4* \
                  /usr/lib/x86_64-linux-gnu/

COPY --from=build /usr/lib/x86_64-linux-gnu/libexif.so* \
                  /usr/lib/x86_64-linux-gnu/

# Existing Boost libraries 
COPY --from=build /usr/local/lib/libboost_json.so* \
                  /usr/local/lib/

COPY --from=build /usr/local/lib/libboost_system.so* \
                  /usr/local/lib/

COPY --from=build /usr/lib/x86_64-linux-gnu/libboost_system.so* \
                  /usr/lib/x86_64-linux-gnu/

# -----------------------------------------------------
# Application-2 (changes in ./data won't invalidate above library layers)
# -----------------------------------------------------

COPY --from=build /opt/mikshi_box/utilities ./utilities

COPY --from=build /opt/mikshi_box/scripts ./scripts

COPY --from=build /opt/sfe_toolkits /opt/sfe_toolkits

COPY --from=build /opt/mikshi_box/data ./data

# -----------------------------------------------------
# Permissions
# -----------------------------------------------------

RUN chmod +x /opt/mikshi_box/scripts/*.sh

# -----------------------------------------------------
# Refresh linker cache
# -----------------------------------------------------

RUN ldconfig

# -----------------------------------------------------
# Environment
# -----------------------------------------------------

ENV LD_LIBRARY_PATH=/opt/mikshi_box/libs:/usr/local/lib:$LD_LIBRARY_PATH

ENV MIKSHI_HOME=/opt/mikshi_box

# -----------------------------------------------------
# Working directory
# -----------------------------------------------------

WORKDIR /opt/mikshi_box/bin

# -----------------------------------------------------
# Startup
# -----------------------------------------------------

ENTRYPOINT ["/opt/mikshi_box/scripts/docker_entrypoint.sh"]

CMD ["./Monitor","../data/Monitor_path.json","-r"]
# ENTRYPOINT AND CMD IS CONVERTED TO SYSTEM LEVEL CALL BY DOCKER:-
# execve(
#     "/opt/mikshi_box/scripts/docker_entrypoint.sh",
#     {
#         "/opt/mikshi_box/scripts/docker_entrypoint.sh",
#         "./Monitor",
#         "../data/Monitor_path.json",
#         "-r",
#         NULL
#     },
#     envp   ,LD_LIBRARY_PATH,PATH any other k-v included in ENV var in declaration.
# );

#launcher process is replaced by init_box.sh and it should at end do like:-
    #exec "$@", where  @ gives sequence to arguments passed to sh.
                      #"$1" = ./Monitor
                      #"$2" = ../data/Monitor_path.json
                      #"$3" = -r
    #so it becomes exec ./Monitor ../data/Monitor_path.json -r
