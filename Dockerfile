FROM ubuntu:22.04
RUN apt update
RUN apt upgrade
RUN apt install -y cmake build-essential g++ ninja