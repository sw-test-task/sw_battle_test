FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y build-essential clang cmake && apt-get clean

COPY src /root/src
COPY CMakeLists.txt /root/CMakeLists.txt

WORKDIR /root
RUN mkdir build
RUN cd build && CC=clang CXX=clang++ cmake .. && cmake --build .

ENTRYPOINT ["/root/build/sw_battle_test"]
