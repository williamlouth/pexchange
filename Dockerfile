FROM ubuntu:23.04


RUN apt update
RUN apt upgrade -y

RUN apt install -y cmake build-essential g++ ninja-build git
RUN apt-get install -y grpc++ libprotobuf-dev protobuf-compiler-grpc libssl-dev
RUN apt install -y uuid-dev pkg-config

RUN git clone --recursive https://gitlab.com/BuildGrid/buildbox/buildbox-common.git
RUN cd buildbox-common && mkdir build && cd build && cmake .. && make -j4 install && cd ../..


RUN git clone --recursive https://gitlab.com/BuildGrid/recc.git
RUN cd recc && mkdir build && cd build && cmake .. && make -j4 install && cd ../..
