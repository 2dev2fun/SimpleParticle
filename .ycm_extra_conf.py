import os
import ycm_core

def Settings(**kwargs):
    return { 'flags': [
        '-x', 'c++',
        '-std=c++17',
        '-Wall',
        '-Wextra'
        '-Werror',
        '-I',       'include',
        '-isystem', 'library/glad/include',
        '-isystem', 'modules/glfw/include',
        '-isystem', 'modules/SimpleMath/include',
    ] }
