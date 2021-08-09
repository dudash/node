ARG FROM_IMAGE
ARG DEVEL_IMAGE

FROM ${DEVEL_IMAGE} as devel

WORKDIR /home/node

RUN cp                                              \
    /opt/rapids/node/.npmrc                         \
    /opt/rapids/node/build/rapidsai-core-*.tgz      \
    /opt/rapids/node/build/nvidia-cuda-*.tgz        \
    /opt/rapids/node/build/rapidsai-rmm-*.tgz       \
    /opt/rapids/node/build/rapidsai-cudf-*.tgz      \
    /opt/rapids/node/build/rapidsai-cuspatial-*.tgz \
    . \
 && npm install --production --omit dev --omit peer --omit optional --legacy-peer-deps --force *.tgz \
 && npm dedupe  --production --omit dev --omit peer --omit optional --legacy-peer-deps --force


FROM ${FROM_IMAGE}

SHELL ["/bin/bash", "-c"]

ENV NVIDIA_DRIVER_CAPABILITIES compute,utility

USER root

# Install dependencies
RUN export DEBIAN_FRONTEND=noninteractive \
 && apt update --fix-missing \
 && apt install -y --no-install-recommends \
    # cuSpatial dependencies
    libgdal-dev \
 # Clean up
 && apt autoremove -y && apt clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

COPY --from=devel --chown=node:node /home/node/node_modules/ /home/node/node_modules/

USER node

WORKDIR /home/node

SHELL ["/bin/bash", "-l"]

CMD ["node"]