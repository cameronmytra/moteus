FROM ubuntu:22.04

ARG USER_ID
ARG GROUP_ID

# Set timezone to avoid interactive prompts
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=UTC

RUN apt-get update
RUN apt-get install -y python3-pip python3-can python3-serial python3-setuptools python3-pyelftools python3-qtpy python3-wheel libncurses5
RUN apt-get install -y curl patch git build-essential

# RUN addgroup --gid $GROUP_ID user
RUN adduser --disabled-password --gecos '' --uid $USER_ID --gid $GROUP_ID user

USER user

# ignore git error "detected dubious ownership in repository at '/src'""
RUN git config --global --add safe.directory /src
