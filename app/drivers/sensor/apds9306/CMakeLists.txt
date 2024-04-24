# Copyright (c) 2023, Daniel Kampert
#
# SPDX-License-Identifier: Apache-2.0
#

if(CONFIG_APDS9306_EMUL)
    zephyr_sources(avago_apds9306_emul.c)
else()
    zephyr_sources(avago_apds9306.c)
endif()