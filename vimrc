
" {{{ Pathogen & Plugin Settings 

" Use pathogen to load further modules
filetype off
call pathogen#runtime_append_all_bundles("plugins")
call pathogen#helptags()

" Supertab settings
let g:SuperTabDefaultCompletionType = "context"

" Taglist settings
"let Tlist_Use_Right_Window = 1
"let Tlist_Enable_Fold_Column = 0
"let Tlist_Exit_OnlyWindow = 1
"let Tlist_Use_SingleClick = 1
"let Tlist_Inc_Winwidth = 0

" }}}

" {{{ Look & Feel

set t_Co=256
"set background=dark
" hi normal   ctermfg=white  ctermbg=black guifg=white  guibg=black
" hi nontext  ctermfg=blue   ctermbg=black guifg=blue   guibg=black

if has("syntax")
    
    syntax on
    
    color wombat256
    " color inkpot
    " color 256-jungle
    " color adrian
    " color calmar256
    " color colorful256
    " color desert256
    " color desert
    " color deveiate
    " color wombat256
    " color xoria256

endif    

" line numbering
set number              " line numbering

" folding
set foldmethod=marker   " autofold on three braces ({{)

" fancy cursor-crosshair
"hi CursorColumn term=none cterm=none ctermbg=52
"hi CursorLine term=none cterm=none ctermbg=52
set cursorcolumn
set cursorline

" strange settings for split windows. they are always minimized to 
" one line, except one. and you can switch nicely... not usable for 
" me but maybe comes handy some day for devices with small screen...
"set winminheight=0
"set winheight=999

" }}}

" {{{ Statusline
"Reminder: add 'warning functions" from stuckoverflow thread

" 2 lines for statusline. Inforbar will be shown on typing command
set laststatus=2

" Overwrite theme colors for statusbar
"hi StatusLine term=reverse ctermfg=4 gui=undercurl guisp=orange

set statusline=
set statusline+=[%n]                                    " buffer nr
set statusline+=%y                                      " filetype
set statusline+=[%{strlen(&fenc)?&fenc:'none'}]         " file encoding
set statusline+=[%{&ff}]                                " fileformat
set statusline+=%r                                      " read only flag
set statusline+=%h                                      " help file flag
set statusline+=%w                                      "  
set statusline+=%m                                      " modified flag

set statusline+=%=                                      " right align
set statusline+=%1*%F%*\                                " full filename
"set statusline+=%1*%t%*\                               " tail of filename
set statusline+=[line\ %l/%L\|%p%%\|char\ %v]           " [line 87/220|39%|char 50]
"set statusline+=[%04.3b@ascii\|\%02.2B@hex]            " [0101@ascii|65@hex]
"set statusline+=[U+%04B]                               " Unicode char under cursor

""Complete thirdparty statuslines 
"set statusline=%t[%{strlen(&fenc)?&fenc:'none'},%{&ff}]%h%m%r%y%=%c,%l/%L\ %P " from scrooloose
"set statusline=[%n]\ %<%.99f\ %h%w%m%r%{exists('*CapsLockStatusline')?CapsLockStatusline():''}%y%=%-16(\ %l,%c-%v\ %)%P " from tpope
"set statusline=%f%w%m%h%1*%r%2*%{VarExists('b:devpath','<Rel>')}%3*%{VarExists('b:relpath','<Dev>')}%{XLockStat()}%=%-15(%l,%c%V%)%P " from frogonwheel

" }}}

" {{{ Language Support
    
filetype on
filetype plugin on
filetype indent on

" Spelling 
highlight SpellBad term=underline gui=undercurl guisp=Red 
set spl=en spell        " english spellchecking
set nospell             " disable by default

" auto-completion & co 
autocmd FileType python set omnifunc=pythoncomplete#Complete
autocmd FileType c set omnifunc=ccomplete#Complete
autocmd FileType javascript set omnifunc=javascriptcomplete#CompleteJS
autocmd FileType xml set omnifunc=xmlcomplete#CompleteTags
autocmd FileType html set omnifunc=htmlcomplete#CompleteTags
autocmd FileType css set omnifunc=csscomplete#CompleteCSS
autocmd FileType php set omnifunc=phpcomplete#CompletePHP
autocmd FileType php let php_sql_query=1
autocmd FileType php let php_htmlInStrings=1

" Do normal tabs for Makefiles
autocmd FileType make set noexpandtab shiftwidth=8

" Map <CTRL>-P to run PHP parser check
autocmd FileType php noremap <C-P> :!php -l %<CR>

" The php completion dictionary is provided by Rasmus: http://lerdorf.com/funclist.txt
"autocmd FileType php set dictionary-=/home/simon/.vim/documentation/php_funclist.txt dictionary+=/home/simon/.vim/documentation/php_funclist.txt

" }}}

" {{{ Editor Settings 

" jump to last position on reopening a file
if has("autocmd")
  au BufReadPost * if line("'\"") > 0 && line("'\"") <= line("$")
    \| exe "normal! g'\"" | endif
endif

" Suffixes that get lower priority when doing tab completion for filenames.
" These are files we are not likely to want to edit or read.
set suffixes=.bak,~,.swp,.o,.so,.out,.bin,.aux,.idx,.jpg,.png,.gif,.avi,.mkv,.mp3,.flac

set nocompatible                    " just to be sure
set backspace=indent,eol,start      " more powerful backspacing
set ttyfast

set tabstop=4
set shiftwidth=4
set softtabstop=4
set expandtab
set smarttab
set smartindent
set autoindent
set showmatch           " Show matching brackets.
set smartcase           " Do smart case matching
set hlsearch            " highlite search term
set incsearch           " search while typing
"set ignorecase         " Do case insensitive matching by default
set autowrite           " save on buffer change
set gdefault            " always assume /g
set ff=unix             " fileformat 
set wildmenu                         " turn on wild menu :e <Tab>
set wildmode=list:longest,full       " set wildmenu to list choice
set showcmd
set noerrorbells        " no error bells
set undolevels=1000     " 1000 undos
set history=50          " keep 50 lines of command line history
set viminfo='20,\"10000 " read/write a .viminfo file
set nobackup            " don't write backup file
set nowritebackup       " dont' write 'old_version'-backup file
"set mouse=a|b          " To play with x11 integration - confusing x11 behavier... 
"set hidden             " Hide buffers when they are abandoned
"set textwidth=0        " Don't wrap lines by default
"set wmh=0              " allow window size 0 - not working as expected...
"set ruler              " show the cursor position all the time
"set novb
"set noeb
"set shiftround

" What is this?
"autocmd CursorMovedI * if pumvisible() == 0|pclose|endif
"autocmd InsertLeave * if pumvisible() == 0|pclose|endif

" }}}

" {{{ Shortcuts  

" This is for working across multiple xterms and/or gvims
" Transfer/read and write one block of text between vim sessions (capture whole line):
"nmap ;w :. w! ~/.vimxfer<CR>      " Write
"nmap ;r :r ~/.vimxfer<CR>         " Read
"nmap ;a :. w! >>~/.vimxfer<CR>    " Append 

" firefox like navigation
nnoremap <silent> <C-PageDown> :next <CR>
nnoremap <silent> <C-PageUp> :prev<CR>
nnoremap <silent> <C-n> :new<CR>

" resize window
if bufwinnr(1)
    map + <C-W>+
    map - <C-W>-
endif

" toggle paste
nnoremap <F2> :set invpaste paste?<CR>
imap <F2> <C-O><F2>
set pastetoggle=<F2>

" run script 
map <F5> :!%:p<CR>

" taglist
nnoremap <silent> <F7> :TlistToggle<CR> 

" nerdtree
nnoremap <silent> <F8> :NERDTreeToggle<CR> 

" folding 
inoremap <F9> <C-O>za
nnoremap <F9> za
onoremap <F9> <C-C>za
vnoremap <F9> zf

" }}}

