docker run -d -v ${PWD}:/root --security-opt seccomp:unconfined -ti --name TP2COMPILER agodio/itba-so-multi-platform:3.0
docker start TP2COMPILER
docker exec -it TP2COMPILER make clean -C/root/Toolchain
docker exec -it TP2COMPILER make clean -C/root/
docker exec -it TP2COMPILER make -C/root/Toolchain
docker exec -it TP2COMPILER make -C/root/
docker stop TP2COMPILER
docker rm TP2COMPILER