
" {{{ Pathogen

" Use pathogen to load further modules from plugins/
filetype off
runtime plugins/vim-pathogen/autoload/pathogen.vim
call pathogen#incubate('plugins/{}')
call pathogen#helptags()

" }}}

" {{{ Look / Colors / Sounds

if $COLORCOUNT == "" || $COLORCOUNT == "256"
    set t_Co=256
    color wombat256
else
    color wombat
endif

if has("syntax")
    syntax on
endif

"set background=dark
" hi normal   ctermfg=white  ctermbg=black guifg=white  guibg=black
" hi nontext  ctermfg=blue   ctermbg=black guifg=blue   guibg=black

" fancy cursor-crosshair
augroup CursorLine
    au!
    au VimEnter,WinEnter,BufWinEnter * setlocal cursorline
    au VimEnter,WinEnter,BufWinEnter * setlocal cursorcolumn
    au WinLeave * setlocal nocursorline
    au WinLeave * setlocal nocursorcolumn
augroup END

" line numbering
set number

" disable extended UI on gvim
if has('gui_running')
    set guioptions-=T  " no toolbar
    set guioptions-=m  " no menubar
    set guioptions-=r  " no right scrollbar
    set guioptions-=L  " no left scrollbar
endif

""" disable sounds
set noerrorbells
set visualbell
if has('gui_running')
    set vb t_vb=
else
    set noeb vb t_vb=
endif

""" Statusline
set laststatus=2

" Not really used, since powerline...
set statusline=[%n]%y[%{strlen(&fenc)?&fenc:'none'}][%{&ff}]%r%h%w%m%=%1*%F%*\ [line\ %l/%L\|%p%%\|char\ %v]

" }}}

" {{{ Editor Settings

""" just to be sure
set nocompatible
set ttyfast
set showcmd

""" environment, encoding, fileformat
set encoding=utf-8
set ff=unix
set shell=/bin/bash

""" tabbing & indentation
set tabstop=4
set shiftwidth=4
set softtabstop=4
set expandtab
set smarttab
set smartindent
set autoindent
"set shiftround

""" performance & hiccups
set lazyredraw

""" buffers
set hidden

""" search/replace
set hlsearch            " highlite search term
set incsearch           " search while typing
set ignorecase          " Do case insensitive matching by default
set smartcase           " Do smart case matching
"set wrapscan           " wrap around
"set gdefault           " always assume /g

""" folding
" foldmethods:
" marker    - folding on three '{'
" syntax    - folding by syntax-highliting
" indent    - folding by indent
" diff      - folding on unchanged lines
set foldmethod=marker

"set foldclose=all      " autoclose folding on leaving
"set foldopen=all       " autoopen fold on enter

""" brackets
set showmatch

""" mouse
"set mouse=a|b          " To play with x11 integration - confusing x11 behavier...

""" save/load
set autowrite           " save on buffer change

" Suffixes that get lower priority when doing tab completion for filenames.
" These are files we are not likely to want to edit or read.
set suffixes=.bak,~,.swp,.o,.so,.out,.bin,.aux,.idx,.jpg,.png,.gif,.avi,.mkv,.mp3,.flac

" wildmenu
set wildmenu
"set wildmode=longest,list,full
set wildmode=longest:full,full
set wildignore=.svn,CVS,.git,.hg,*.o,*.a,*.mo,*.la,*.so,*.obj,*.swp,*.xpm,*.exe,*.rar

" undo/backup/swp/info/...
set history=75          " keep 75 lines of command line history
set viminfo='20,\"10000 " read/write a .viminfo file  """

set undolevels=1000     " 1000 undos
set undoreload=10000    " number of lines to save for undo
set undodir=~/.vim/tmp/undo
set undofile

"set noswapfile
set dir=~/.vim/tmp/swap
set swapfile

"set nobackup            " don't write backup file
"set nowritebackup       " dont' write 'old_version'-backup file  """
set backupdir=~/.vim/tmp/backup
set backup
set writebackup

" jump to last position on reopening a file
if has("autocmd")
  au BufReadPost * if line("'\"") > 0 && line("'\"") <= line("$")
    \| exe "normal! g'\"" | endif
endif

" automatically give executable permissions if file begins with #! and contains '/bin/' in the path
" au BufWritePost * if getline(1) =~ "^#!" | if getline(1) =~ "/bin/" | silent !chmod a+x <afile> | endif | endif

" auto-reload vimrc on save
"autocmd BufWritePost .vimrc source ~/.vimrc
"autocmd BufWritePost vimrc source ~/.vimrc

" strange settings for split windows. they are always minimized to
" one line, except one. and you can switch nicely... not usable for
" me but maybe comes handy some day for devices with small screen...
"set winminheight=0
"set winheight=999

""" navigation
set scrolloff=3                     " min 3 lines above/below cursor while scrolling
set backspace=indent,eol,start      " more intuitive backspacing in insert mode

" }}}

" {{{ Keymappings & Plugin Settings

""" Set a more intuitive <Leader>
let mapleader = ","

""" firefox-like navigation
nnoremap <silent> <C-PageDown> :next<CR>
nnoremap <silent> <C-PageUp> :prev<CR>
nnoremap <silent> <C-n> :new<CR>

""" toggle folding
nnoremap <Leader>f za
vnoremap <Leader>f zf

""" toggle all foldings (todo: fix toggle)
nnoremap <Leader><S-f> zR
vnoremap <Leader><S-f> zM

""" toggle paste
nnoremap <F2> :set invpaste paste?<CR>
imap <F2> <C-O><F2>
set pastetoggle=<F2>

""" disable highliting temp
"nmap <F3> :set hls!<Bar>set hls?<CR>
nmap <F3> :noh<CR>

""" toggle ignorecase
map <F4> :set ic!<bar>set ic?<cr>

""" run script
map <F5> :!%:p<CR>

""" [plugin] gundo
nmap <F6> :GundoToggle<CR>

""" [plugin] tagbar
nmap <F9> :TagbarToggle<CR>
let g:tagbar_phpctags_bin='/home/simon/.lib/phpctags/phpctags'

""" scrollsync
map <F10> :set scb!<bar>set scb?<cr>

""" [plugin] Snipmate
let g:snips_dir = "~/.vim/snippets/"
let g:snips_author = 'Simon Schiele'
"let g:snips_trigger_key_backwards='<none>'

""" [plugin] vim-ack
let g:ackprg="ack-grep -H --nocolor --nogroup --column"

""" [plugin] Supertab
let g:SuperTabDefaultCompletionType = "context"
"let g:SuperTabContextDefaultCompletionType = "<C-X><C-O>"
"let g:SuperTabContextDefaultCompletionType = "<c-p>"

" omni
"let g:SuperTabDefaultCompletionType = "\<c-x>\<c-o>"

" user
"let g:SuperTabDefaultCompletionType = "<c-x><c-u>"

"let g:SuperTabCompletionContexts = ['s:ContextText', 's:ContextDiscover']
"let g:SuperTabContextTextOmniPrecedence = ['&omnifunc', '&completefunc']
"let g:SuperTabContextDiscoverDiscovery = ["&completefunc:<c-x><c-u>", "&omnifunc:<c-x><c-o>"]
"let g:SuperTabCrMapping = 1

let g:SuperTabCrClosePreview = 1
let g:SuperTabClosePreviewOnPopupClose = 1

let g:SuperTabMappingForward = '<s-tab>'
let g:SuperTabMappingBackward = '<s-c-tab>'
let g:SuperTabMappingTabLiteral = '<tab>'

autocmd FileType *
  \ if &omnifunc != '' |
  \   call SuperTabChain(&omnifunc, "<c-p>") |
  \   call SuperTabSetDefaultCompletionType("<c-x><c-u>") |
  \ endif

set completeopt=longest,menuone

""" [plugin] Gundo
nnoremap <Leader>u :GundoToggle<CR>
let g:gundo_width = 65
"let g:gundo_preview_height = 20
"let g:gundo_right = 1
"let g:gundo_preview_statusline =
"let g:gundo_tree_statusline =

""" [plugin] NerdTree
let g:NERDTreeQuitOnOpen = 1
autocmd vimenter * if !argc() | NERDTree | endif
autocmd bufenter * if (winnr("$") == 1 && exists("b:NERDTreeType") && b:NERDTreeType == "primary") | q | endif
nnoremap <silent> <F8> :NERDTreeToggle<CR>

""" [plugin] airline
let g:airline_enable_fugitive=1
let g:airline_enable_syntastic=1
let g:airline_theme='dark' " dark, light, simple, badwolf, solarized, solarized2
if $POWERLINE_FONT == "true"
    let g:airline_powerline_fonts=1
endif

" }}}

" {{{ Unite.vim

" matcher -> fuzzy
call unite#filters#matcher_default#use(['matcher_fuzzy'])

" Custom mappings for the unite buffer
autocmd FileType unite call s:unite_settings()
function! s:unite_settings()
  " Play nice with supertab
  let b:SuperTabDisabled=1

  " close on Ctrl+c
  imap <buffer> <C-c> <C-c>q
  map <buffer> <C-c> <C-c>q
endfunction

" open files
nnoremap <leader>o :<C-u>Unite -toggle -no-split -buffer-name=files -start-insert file_rec/async<cr>

" bufferbrowser
nnoremap <leader>b :<C-u>Unite -toggle -no-split -buffer-name=buffer -start-insert buffer<cr>

" yank history
let g:unite_source_history_yank_enable = 1
nnoremap <leader>y :<C-u>Unite -toggle -no-split -buffer-name=yank history/yank<cr>

" [plugin] unite-cleanup
nnoremap <leader>C :Unite -toggle -complete -auto-resize -direction=bot -start-insert -buffer-name=cleanup cleanup<cr>
"autocmd BufEnter * UpdateCleanupHighlite()
"autocmd BufWinEnter UpdateCleanupHighlite()<cr>
"autocmd InsertEnter UpdateCleanupHighlite()<cr>

" [plugin] unite-outline
"nnoremap <leader>t :Unite outline<cr>

" [plugin] unite-ack
"nnoremap <leader>a :Unite ack<cr>
"g:unite_source_ack_command="ack-grep --nocolor --nogroup"
"g:unite_source_ack_enable_highlight=1
"g:unite_source_ack_search_word_highlight=Search
"g:unite_source_ack_ignore_case=0
"g:unite_source_ack_enable_print_cmd=1
"let g:unite_source_ack_targetdir_shortcut={}
"let g:unite_source_ack_targetdir_shortcut={}

" }}}

" {{{ Language Support

filetype on
filetype plugin on
filetype plugin indent on
filetype indent on

" {{{ Spelling

highlight SpellBad term=underline gui=undercurl guisp=Red
set spl=en spell        " english spellchecking
set nospell             " disable by default
let g:myLang = 0
let g:myLangList = ['nospell', 'de', 'en']
function! MySpellLang()
  "loop through languages
  if g:myLang == 0 | setlocal nospell | endif
  if g:myLang == 1 | let &l:spelllang = g:myLangList[g:myLang] | setlocal spell | endif
  if g:myLang == 2 | let &l:spelllang = g:myLangList[g:myLang] | setlocal spell | endif
  echomsg 'language:' g:myLangList[g:myLang]
  let g:myLang = g:myLang + 1
  if g:myLang >= len(g:myLangList) | let g:myLang = 0 | endif
endfunction
map <F7> :<C-U>call MySpellLang()<CR>

" }}}

" {{{ php
autocmd FileType php set omnifunc=phpcomplete#CompletePHP
autocmd FileType php set ft=php.javascript.html
autocmd FileType php let php_sql_query=1
autocmd FileType php let php_htmlInStrings=1

" Map <CTRL>-P to run PHP parser check
autocmd FileType php noremap <C-P> :!php -l %<CR>

" The php completion dictionary is provided by Rasmus: http://lerdorf.com/funclist.txt
"autocmd FileType php set dictionary-=/home/simon/.vim/documentation/php_funclist.txt dictionary+=/home/simon/.vim/documentation/php_funclist.txt

" php manual
function! OpenPhpFunction (keyword)
    let proc_keyword = substitute(a:keyword , '_', '-', 'g')
    exe 'split'
    exe 'enew'
    exe "set buftype=nofile"
    exe 'silent r!lynx -dump -nolist http://www.php.net/manual/en/print/function.'.proc_keyword.'.php'
    exe 'norm gg'
    exe 'call search ("' . a:keyword .'")'
    exe 'norm dgg'
    exe 'call search("User Contributed Notes")'
    exe 'norm dGgg'
endfunction
autocmd FileType php noremap <C-k> :call OpenPhpFunction('<C-r><C-w>')<CR>
" }}}

""" html/xml/css
autocmd FileType html set omnifunc=htmlcomplete#CompleteTags
autocmd FileType css set omnifunc=csscomplete#CompleteCSS
autocmd FileType xml set omnifunc=xmlcomplete#CompleteTags
autocmd FileType html set ft=html.javascript

""" JavaScript
autocmd FileType javascript set omnifunc=javascriptcomplete#CompleteJS
autocmd FileType javascript set ft=javascript.html

""" Python
autocmd FileType python set omnifunc=pythoncomplete#Complete

""" C
autocmd FileType c set omnifunc=ccomplete#Complete

""" make
autocmd FileType make set noexpandtab shiftwidth=8

""" binary
"augroup Binary au! au BufReadPre *.bin let &bin=1 au BufReadPost *.bin if &bin | %!xxd au BufReadPost  *.bin set filetype=xxd | endif au BufWritePre *.bin if &bin | %!xxd -r au BufWritePre *.bin endif au BufWritePost *.bin if &bin | %!xxd au BufWritePost *.bin set nomod | endif

" }}}

