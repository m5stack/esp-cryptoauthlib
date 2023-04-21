#
# CMakeLists.txt file for cryptoauthlib
#
cmake_minimum_required( VERSION 3.5 )
set( CRYPTOAUTHLIB_DIR      "cryptoauthlib/lib" )
set( COMPONENT_SRCDIRS      "${CRYPTOAUTHLIB_DIR}/atcacert"
                            "${CRYPTOAUTHLIB_DIR}/calib"
                            "${CRYPTOAUTHLIB_DIR}/crypto"
                            "${CRYPTOAUTHLIB_DIR}/crypto/hashes"
                            "${CRYPTOAUTHLIB_DIR}/host"
                            "${CRYPTOAUTHLIB_DIR}/mbedtls"
                            "${CRYPTOAUTHLIB_DIR}"
                            "${CRYPTOAUTHLIB_DIR}/../app/tng"
                            "port"
                            )

set( COMPONENT_SRCS         "${CRYPTOAUTHLIB_DIR}/hal/atca_hal.c"
                            "${CRYPTOAUTHLIB_DIR}/hal/hal_freertos.c"
                            "${CRYPTOAUTHLIB_DIR}/hal/hal_esp32_timer.c"
                            "${CRYPTOAUTHLIB_DIR}/../third_party/atca_mbedtls_patch.c"
                            )

set( COMPONENT_INCLUDEDIRS  "${CRYPTOAUTHLIB_DIR}/"
                            "${CRYPTOAUTHLIB_DIR}/hal"
                            "${CRYPTOAUTHLIB_DIR}/../app/tng"
                            "${CRYPTOAUTHLIB_DIR}/../third_party"
                            "port"
                            )

set( COMPONENT_PRIV_INCLUDEDIRS "port/include" )

set( COMPONENT_REQUIRES         "mbedtls" "freertos" "driver" "Core2-for-AWS-IoT-Kit" )

# Don't include the default interface configurations from cryptoauthlib
set( COMPONENT_EXCLUDE_SRCS "${CRYPTOAUTHLIB_DIR}/atca_cfgs.c" )
set( COMPONENT_CFLAGS       "ESP32" )

idf_component_register(     SRC_DIRS            "${COMPONENT_SRCDIRS}"
                            INCLUDE_DIRS        "${COMPONENT_INCLUDEDIRS}"
                            PRIV_INCLUDE_DIRS   "${COMPONENT_PRIV_INCLUDEDIRS}"
                            PRIV_REQUIRES       "${COMPONENT_PRIV_REQUIRES}"
                            REQUIRES            "${COMPONENT_REQUIRES}"
                            EXCLUDE_SRCS        "${COMPONENT_EXCLUDE_SRCS}"
                            )

if( IDF_VERSION_MAJOR EQUAL 4 AND IDF_VERSION_MINOR LESS_EQUAL 3 AND IDF_VERSION_PATCH LESS 1 )
    target_compile_definitions(${COMPONENT_LIB} PUBLIC "-DATCA_ENABLE_DEPRECATED" )
endif()

target_sources( ${COMPONENT_LIB} PRIVATE ${COMPONENT_SRCS} )
target_compile_definitions( ${COMPONENT_LIB} PRIVATE ${COMPONENT_CFLAGS} )
target_compile_options( ${COMPONENT_LIB} PRIVATE -Wno-pointer-sign )
