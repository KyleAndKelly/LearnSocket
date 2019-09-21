#将某个目录下的的源文件以列表的形式存放在变量SRC_LIST中
#aux_source_directory(. SRC_LIST)
#手动添加源文件名称  生成可执行文件simple_client
add_executable(poll_client  client.cpp)
#手动添加源文件名称 生成可执行文件simple_server
add_executable(poll_server  server.cpp )