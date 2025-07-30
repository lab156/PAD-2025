# Use Alpine Linux as the base image
FROM alpine:latest

# Install required packages
RUN apk update && apk add --no-cache \
    bash \
    git

# Clone Neofetch and make it available
RUN git clone https://github.com/dylanaraps/neofetch /opt/neofetch && \
    ln -s /opt/neofetch/neofetch /usr/local/bin/neofetch

# Set the default shell to bash
SHELL ["/bin/bash", "-c"]

# Set the default command
CMD ["bash"]
