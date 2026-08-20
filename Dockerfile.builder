FROM debian:bookworm
RUN sed -i 's|deb.debian.org|ftp.fr.debian.org|g' /etc/apt/sources.list.d/debian.sources 2>/dev/null || sed -i 's|deb.debian.org|ftp.fr.debian.org|g' /etc/apt/sources.list
RUN dpkg --add-architecture arm64 && \
    apt-get update && \
    apt-get install -y --fix-missing --no-install-recommends \
    git crossbuild-essential-arm64 cmake make pkg-config \
    libssl-dev:arm64 libsdl2-dev:arm64 libsdl2-image-dev:arm64 libsdl2-ttf-dev:arm64 \
    libdrm-dev:arm64 libgbm-dev:arm64 \
    libavcodec-dev:arm64 libavformat-dev:arm64 libavutil-dev:arm64 libswscale-dev:arm64 \
    libxml2-dev:arm64 libnl-3-dev:arm64 libnl-genl-3-dev:arm64 libnl-route-3-dev:arm64 \
    libnm-dev:arm64 libpolkit-gobject-1-dev:arm64 && \
    rm -rf /var/lib/apt/lists/*
ENV PKG_CONFIG_PATH=/usr/lib/aarch64-linux-gnu/pkgconfig
WORKDIR /vanilla
