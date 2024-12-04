# find ngtcp2
find_package(ngtcp2 REQUIRED)

# link ngtcp2
target_link_libraries(trojan PRIVATE ngtcp2)
