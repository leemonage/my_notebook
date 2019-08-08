" @s.egorov
" 2018.04

set nocompatible
filetype off

" let's go!

set number

set autoindent
set smartindent
set smarttab
set shiftwidth=4
set softtabstop=4
set tabstop=4
set expandtab

colo slate
syntax on

" my binds

inoremap jj <ESC>

inoremap ( ()<Left>
inoremap <expr> )  strpart(getline('.'), col('.')-1, 1) == ")" ? "\<Right>" : ")"
inoremap {      {}<Left>
inoremap {<CR>  {<CR>}<Esc>O
inoremap {{     {
inoremap {}     {}
inoremap <expr> ' strpart(getline('.'), col('.')-1, 1) == "\'" ? "\<Right>" : "\'\'\<Left>"
inoremap <expr> " strpart(getline('.'), col('.')-1, 1) == "\"" ? "\<Right>" : "\"\"\<Left>"
map <C-c> :%w !pbcopy<CR><CR>
map <C-v> :r !pbpaste<CR><CR>

" plugins

set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
Plugin 'VundleVim/Vundle.vim'
Plugin 'benmills/vimux'
Plugin 'scrooloose/nerdtree'
Plugin 'dracula/vim'
call vundle#end()
filetype plugin indent on

" vimux options and binds

let g:VimuxOrientation="h"
let g:VimuxHeight="32"
map <C-d> :call VimuxCloseRunner()<CR>
map <C-t> :wall<CR>:call VimuxRunCommand("clang++ -std=c++17 -w -DLOCAL code.cpp -o code")<CR>:cw<CR>
map <C-r> :call VimuxRunCommand("./code <file.in")<CR>
map <C-e> :call VimuxRunCommand("python3 main.py")<CR>
