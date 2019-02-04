FROM ubuntu:18.04

ENV DEBIAN_FRONTEND=noninteractive

WORKDIR /usr/local/src

# Install pd from https://puredata.info/downloads/purr-data
RUN apt-get update \
    && apt-get upgrade -y \
    && apt-get -y install software-properties-common \
    && apt-get -y install \
        build-essential \
        gem-dev \
        git \
        graphicsmagick-libmagick-dev-compat \
        libavifile-0.7-dev \
        libdv4-dev \
        libfreeimage-dev \
        libmpeg3-dev \
        libquicktime-dev \
        libv4l-dev \
        make \
        puredata-dev

# Copy sources
COPY . /usr/local/src

# Compile
CMD ["make", "all-docker"]
