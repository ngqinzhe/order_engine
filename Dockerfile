FROM debian:latest
RUN apt-get -y update \
  && apt-get -y install build-essential \
  cmake \
  && apt-get clean
COPY . /app
RUN cd /app && make build
