FROM public.ecr.aws/docker/library/alpine:latest as base

RUN apk add --no-cache cmake gcc g++ ninja linux-headers

COPY ./ /var/work

RUN mkdir -p /var/work/build-folder && cd /var/work/build-folder && cmake -GNinja .. && cmake --build .

FROM public.ecr.aws/docker/library/alpine:latest as runtime

RUN apk add --no-cache libstdc++ docker-cli

ADD ./resources/configs /var/config

COPY --from=base /var/work/build-folder/updater_app /usr/local/bin/

ENTRYPOINT ["/usr/local/bin/updater_app"]
