# Use Alpine Linux as the base image
FROM alpine:latest

# Install required packages
# libc-dev incluye stdio.h
RUN apk update && apk add --no-cache \
    bash \
    git \
    gcc \
    make \
    libc-dev

# Clone Neofetch and make it available
RUN git clone https://github.com/dylanaraps/neofetch /opt/neofetch && \
    ln -s /opt/neofetch/neofetch /usr/local/bin/neofetch

# Clone the class repository
RUN git clone https://github.com/lab156/PAD-2025.git /opt/PAD-2025


# Compile some source file
# Generar el ejecutable criba
RUN cd /opt/PAD-2025/eratostenes && \
    make clean && \
    make

# Set the default shell to bash
SHELL ["/bin/bash", "-c"]

# Set the default command
CMD ["bash"]

# build with:
# docker build --tag pad_alpine .
