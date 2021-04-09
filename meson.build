project('awb','cpp')

cpp_files = [
'src/main.cpp',
'src/http/http.cpp',
'src/http/https.cpp',
'src/parsing/dom.cpp',
'src/parsing/parser.cpp'

]

cpp_args = ['-Wall','-Wextra','-std=c++11','-pedantic']
link_args = ['-lssl','-lcrypto']
executable('awb',cpp_files,c_args: cpp_args,link_args: link_args)
