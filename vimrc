
" {{{ pathogen (plugin: https://github.com/tpope/vim-pathogen.git)

""" Use pathogen to load further modules from plugins/
filetype off
runtime plugins/pathogen/autoload/pathogen.vim
call pathogen#infect('plugins/{}')
call pathogen#helptags()

" }}}

" {{{ environment

""" just to be sure

set nocompatible
set ttyfast
set showcmd
filetype plugin on
filetype plugin indent on

set encoding=utf-8              " default encoding 'utf-8'
set ff=unix                     "
set shell=/bin/bash             "
let readline_has_bash = 1       " readline + bash

""" set the <Leader> mapping
let mapleader = ","
let g:mapleader = ","

""" some drawing settings
"set ttimeoutlen=50             " todo
"set lazyredraw                 " performance + hiccups

""" some input settings
set backspace=indent,eol,start          " more intuitive backspacing in insert mode
map q <Nop>                             " disable recording
set nowrap
"set list                               " show unprintable characters
"set fillchars=vert:┃,diff:⎼,fold:⎼     " it's about borders?!
"set virtualedit=onemore                 " allow for cursor beyond last character

" }}}

" {{{ cmd

" buffer stuff
set browsedir=buffer    " open path should be on pwd of file in buffer

" Suffixes that get lower priority when doing tab completion for filenames.
" These are files we are not likely to want to edit or read.
set suffixes=.bak,~,.swp,.o,.so,.out,.bin,.aux,.idx,.jpg,.png,.gif,.avi,.mkv,.mp3,.flac

set wildmenu
"set wildmode=longest,list,full
set wildmode=longest:full,full
set wildignore=.svn,CVS,.git,.hg,*.o,*.a,*.mo,*.la,*.so,*.obj,*.swp,*.xpm,*.exe,*.rar

" }}}

" {{{ colors / colorscheme

""" colorcount stuff deactivated at the moment. crappy idea...
" if $COLORCOUNT == "" || $COLORCOUNT == "256"
"     set t_Co=256
"     color wombat256
" else
"     color wombat
" endif

" solarized, wombat
let theme = 'solarized'

if has("syntax")
    syntax on

    set t_Co=256
    set background=dark

    if theme == 'solarized'
        " let g:solarized_bold = 1
        " let g:solarized_italic = 1
        " let g:solarized_underline = 0
        let g:solarized_contrast = 'high'
        let g:solarized_visibility = 'low'
        let g:solarized_termtrans = 1
        let g:solarized_termcolors = 16
        " let g:solarized_termcolors = 256

        colorscheme solarized

    elseif theme == 'wombat'
        colorscheme wombat256

    endif

    set synmaxcol=501 " process highliting on lines <= 501 chars
endif

""" hi overwrite
" hi normal   ctermfg=white  ctermbg=black guifg=white  guibg=black
" hi nontext  ctermfg=blue   ctermbg=black guifg=blue   guibg=black

" }}}

" {{{ sounds

set noerrorbells
set visualbell

if has('gui_running')
    set vb t_vb=
else
    set noeb vb t_vb=
endif

" }}}

" {{{ print

set printoptions=paper:a4
set printoptions=number:y " put line numbers on hardcopy

" }}}

" {{{ undo (todo)

"set undolevels=500      " 500 undos
"set undoreload=10000    " number of lines to save for undo
"set undodir=~/.vim/tmp/undo
"set undofile

" }}}

" {{{ backup / swap / history / viminfo / ... (todo)

set history=1000        " keep 1000 lines of command line history

" Tell vim to remember certain things when we exit
" "  '10  :  marks will be remembered for up to 10 previously edited files
" "  "100 :  will save up to 100 lines for each register
" "  :20  :  up to 20 lines of command-line history will be remembered
" "  %    :  saves and restores the buffer list
" "  n... :  where to save the viminfo files
" " set viminfo='10,\"100,:20,%,n~/.viminfo'
"set viminfo='20,\"10000 " read/write a .viminfo file  """

set noswapfile
"set dir=~/.vim/tmp/swap
"set swapfile

set nobackup            " don't write backup file
"set nowritebackup       " dont' write 'old_version'-backup file  """
"set backupdir=~/.vim/tmp/backup
"set backup
"set writebackup

" jump to last position on reopening a file
if has("autocmd")
  au BufReadPost * if line("'\"") > 0 && line("'\"") <= line("$")
    \| exe "normal! g'\"" | endif
endif

" }}}

" {{{ cursor

""" fancy cursor-crosshair
augroup CursorLine
    au!
    au VimEnter,WinEnter,BufWinEnter * setlocal cursorline
    au VimEnter,WinEnter,BufWinEnter * setlocal cursorcolumn
    au WinLeave * setlocal nocursorline
    au WinLeave * setlocal nocursorcolumn
augroup END

""" lines around the cursor
"set scrolloff=3        " min 3 lines above/below cursor while scrolling
set scrolloff=999       " cursor centered

" }}}

" {{{ mouse

"set mouse=a|b   " play with x11 mouse integration - confusing behavier...

" }}}

" {{{ save

set autoread
set autowrite       " save on buffer change

" Fast saving
nmap <leader>w :w!<cr>  " keymapping:<leader>w _save instantly

""" :w!! to save as sudo
cmap w!! w !sudo tee % >/dev/null

" }}}

" {{{ windows

"" strange settings for split windows. they are always minimized to
"" one line, except one. and you can switch nicely... not usable for
"" me but maybe comes handy some day for devices with small screen...
"set winminheight=0
"set winheight=999

" }}}

" {{{ statusline / airline (plugin: https://github.com/bling/vim-airline.git)

""" classic statusline, not really used since power-/airline...
set statusline=[%n]%y[%{strlen(&fenc)?&fenc:'none'}][%{&ff}]%r%h%w%m%=%1*%F%*\ [line\ %l/%L\|%p%%\|char\ %v]

set laststatus=2    " don't combine status- & commandline

""" todo: ????
" :AirlineToggleWhitespace
" :AirlineToggle

""" airline look
" themes: badwolf, base16, bubblegum, dark, hybrid, jellybeans, kalisi, kolor,
" laederon, light, lucius, luna, molokai, monochrome, murmur, powerlineish,
" raven, serene, silver, simple, solarized, sol, tomorrow, ubaryd,
" understated, wombat, zenburn
let g:airline_powerline_fonts=1
let g:airline_theme='base16'

let g:airline_inactive_collapse=1      " inactive windows have only filename
let g:airline_exclude_preview=0        " no airline in preview_window
let g:airline_detect_paste=1
let g:airline_detect_modified=1
let g:airline_detect_iminsert=1
"let g:airline_exclude_filetypes=[]    " filetypes which have no airline
"let g:airline_exclude_filenames=[]    " filenames which have no airline

let g:airline#extensions#tagbar#enabled=1    " tagbar
let g:airline#extensions#tabline#show_buffers = 1
"let g:airline#extensions#tabline#show_tabs = 1

let g:airline#extensions#tabline#enabled=1   " display open buffers in tabline
let g:airline#extensions#tabline#buffer_min_count=2
"let g:airline#extensions#tabline#left_sep = ' '
"let g:airline#extensions#tabline#left_alt_sep = '|'

" smart algorithm, uniquifies buffers names with similar filename
"let g:airline#extensions#tabline#formatter='unique_tail_improved'

"let g:bufferline_echo =

" airline->git
let g:airline_enable_fugitive=1
"let g:airline#extensions#branch#enabled=1           "
"let g:airline#extensions#branch#empty_message = ''
"let g:airline#extensions#hunks#enabled=1            " enable/disable showing a summary of changed hunks under source control
"let g:airline#extensions#hunks#non_zero_only = 0    " enable/disable showing only non-zero hunks
"let g:airline#extensions#hunks#hunk_symbols = ['+', '~', '-']

" csv
" let g:airline#extensions#csv#enabled=1      " csv.vim
" let g:airline#extensions#csv#column_display = 'Number' " (default)
" let g:airline#extensions#csv#column_display = 'Name'

" syntastic
let g:airline_enable_syntastic=1
let g:airline#extensions#syntastic#enabled=1

" airline->whitespace
let g:airline#extensions#whitespace#enabled=1
let g:airline#extensions#whitespace#show_message = 1
let g:airline#extensions#whitespace#trailing_format = 'trailing[%s]'
let g:airline#extensions#whitespace#mixed_indent_format = 'mixed-indent[%s]'
"let g:airline#extensions#whitespace#symbol = '!'
"let g:airline#extensions#whitespace#checks = [ 'indent', 'trailing' ]

" configure the maximum number of lines where whitespace checking is enabled
"let g:airline#extensions#whitespace#max_lines = 20000

"let g:airline#extensions#ctrlp#color_template = 'insert' " (default)
"let g:airline#extensions#ctrlp#color_template = 'normal'
"let g:airline#extensions#ctrlp#color_template = 'visual'
"let g:airline#extensions#ctrlp#color_template = 'replace'

" virtualenv <https://github.com/jmcantrell/vim-virtualenv>
"let g:airline#extensions#virtualenv#enabled = 1  " enable/disable virtualenv integration >

" airline symbols
"if !exists('g:airline_symbols')
"    let g:airline_symbols = {}
"endif

" unicode symbols
"let g:airline_left_sep = ''
"let g:airline_right_sep = ''
"let g:airline_left_sep='»'
"let g:airline_right_sep='«'
"let g:airline_left_sep='▶'
"let g:airline_right_sep='◀'
"let g:airline_left_alt_sep = ''
"let g:airline_right_alt_sep = ''

"let g:airline_linecolumn_prefix = ' '
"let g:airline_symbols.linenr='␊'
"let g:airline_symbols.linenr='␤'
"let g:airline_symbols.linenr='¶'
"let g:airline_symbols.branch='⎇'
"let g:airline_symbols.paste='ρ'
"let g:airline_symbols.paste='Þ'
"let g:airline_symbols.paste='∥'
"let g:airline_symbols.whitespace='Ξ'
"let g:airline#extensions#branch#symbol = ' '
"let g:airline#extensions#readonly#symbol = ''

" }}}

" {{{ buffers

set hidden      " hide buffers instead of closing them

" switch buffers with ctrl+up/down
" to make this work in gnome-terminal you need to deactivate the official
" keymappings for switching tabs

" keymapping:<C-PageDown> _next buffer
nnoremap <silent> <C-PageDown> :bn<CR>

" keymapping:<C-PageDown> _previous buffer
nnoremap <silent> <C-PageUp> :bp<CR>

" :B ghetto bufferlist
command! -nargs=? -bang B if <q-args> != '' | exe 'buffer '.<q-args> | else | ls<bang> | let buffer_nn=input('Choose buffer: ') | if buffer_nn != '' | exe buffer_nn != 0 ? 'buffer '.buffer_nn : 'enew' | endif | endif

" }}}

" {{{ line numbers / numbers (plugin: https://github.com/b3niup/numbers.vim.git)

set number          " line numbering

" numbers.vim: toggle keymapping
nnoremap <silent> <F4> :NumbersToggle<CR>   " keymapping:<F4> _toggle numbers (normal/relative/disable)

" numbers.vim: windows where not to show numbers at all
let g:numbers_exclude = ['minibufexpl', 'nerdtree', 'unite', 'tagbar', 'startify', 'gundo', 'vimshell', 'w3m']

" }}}

" {{{ brackets

set matchpairs+=<:> " add < > to chars that form pairs (see % command)
set matchtime=1 " show matching brackets quicker than default
set showmatch

" }}}

" {{{ indentation

set tabstop=4       " how many char a tab stands for (affects existing text)
set shiftwidth=4    " indentation 4 spaces
set softtabstop=4   " indentation 4 spaces on <tab> (in insert mode)
set expandtab       "
set smarttab        "
set autoindent      "
set smartindent     " tries 'to do the right thing' - sometimes crazy, mostly ok
"set cindent        " stricter rules for C
"set shiftround     "

""" don't lose visual selection after doing indents
"vnoremap > >gv
"vnoremap < <gv

" }}}

" {{{ search / replace

set hlsearch        " highlite search term
set incsearch       " search while typing
set ignorecase      " Do case insensitive matching by default
set smartcase       " ignore case if pattern if all lowercase, sensitive otherwise
"set wrapscan       " wrap around
"set gdefault       " always assume /g

""" disable highliting temporary (afterddiwpp search)
nnoremap <silent> <F2> :noh<CR>     " keymapping:<F2> _clear search highliting

""" toggle ignorecase
map <F3> :set ic!<bar>set ic?<cr>   " keymapping:<F3> _toggle ignorecase for search

" }}}

" {{{ folding

""" default foldmethod
" marker    - folding on marker (default {{{ -> }}})
" syntax    - folding by syntax
" indent    - folding by indent
" might be overwritten by filetype later on
set foldmethod=marker

" Add a bit extra margin to the left
set foldcolumn=1

""" autofold
" set foldopen=all      " autoopen fold on cursor
" set foldclose=all     " autoclose folding on leaving

""" toggle folding under cursor with <leader>f
nnoremap <Leader>f za   " keymapping:<leader>f _toggle folding
vnoremap <Leader>f zf   " keymapping:<leader>f _toggle folding

""" toggle all foldings (todo: fix)
" nnoremap <Leader><S-f> zR     " keymapping:<leader>XXX _toggle all foldings
" vnoremap <Leader><S-f> zM

function! FoldText() " {{{
    let line = getline(v:foldstart)

    let nucolwidth = &fdc + &number * &numberwidth
    let windowwidth = winwidth(0) - nucolwidth - 3
    let foldedlinecount = v:foldend - v:foldstart

    " expand tabs into spaces
    let onetab = strpart('          ', 0, &tabstop)
    let line = substitute(line, '\t', onetab, 'g')

    let line = strpart(line, 0, windowwidth - 2 -len(foldedlinecount))
    let fillcharcount = windowwidth - len(line) - len(foldedlinecount)
    return line . '…' . repeat(" ",fillcharcount) . foldedlinecount . '…' . ' '
endfunction " }}}

set foldtext=FoldText()

" }}}

" {{{ spelling (de, en)

highlight SpellBad term=underline gui=undercurl guisp=Red
set spl=en spell        " english spellchecking
set nospell             " disable by default
let g:myLang = 0
let g:myLangList = ['nospell', 'de', 'en']
function! MySpellLang()
  let g:myLang = g:myLang + 1
  if g:myLang >= len(g:myLangList) | let g:myLang = 0 | endif

  if g:myLang == 0 | setlocal nospell | endif
  if g:myLang == 1 | let &l:spelllang = g:myLangList[g:myLang] | setlocal spell | endif
  if g:myLang == 2 | let &l:spelllang = g:myLangList[g:myLang] | setlocal spell | endif
  echomsg 'language:' g:myLangList[g:myLang]
endfunction
nmap <F7> :<C-U>call MySpellLang()<CR>      " keymapping:<F7> _Toggle spellcheck & switch languages

" }}}

" {{{ remote editing

let g:netrw_altv = 1          " change from left to right splitting
let g:netrw_fastbrowse = 2    " 0=cache nothing, 1=reuse when browsing, 2=cache always
let g:netrw_keepdir = 0       " keep local curdir
let g:netrw_liststyle = 2     " wide listing (multiple files in columns)
let g:netrw_silent = 1        " transfer silent
let g:netrw_special_syntax = 1  " highlite some filetypes

" }}}

" {{{ filebrowser / nerdtree (plugin: todo)

let g:NERDTreeQuitOnOpen = 1

autocmd vimenter * if !argc() | NERDTree | endif
autocmd bufenter * if (winnr("$") == 1 && exists("b:NERDTreeType") && b:NERDTreeType == "primary") | q | endif

nnoremap <silent> <F9> :NERDTreeToggle<CR>      " keymapping:todo

" }}}

" {{{ ctags / easytags (plugin: todo)

"set tags=tags;$HOME/.vim/tags/ "recursively searches directory for 'tags' file

let g:easytags_suppress_report = 1
let g:easytags_suppress_ctags_warning = 1

" }}}

" {{{ tag-browser / tagbar (plugin: todo)

nmap <F10> :TagbarToggle<CR>        " keymapping:todo

let g:tagbar_usearrows = 1
let g:tagbar_phpctags_bin='/home/simon/.lib/phpctags/phpctags'

" }}}

" {{{ tag-browser / taglist (plugin: todo)

"let Tlist_Ctags_Cmd='/usr/bin/ctags'       " point taglist to ctags
"let Tlist_GainFocus_On_ToggleOpen = 1      " Focus on the taglist when its  toggled
"let Tlist_Close_On_Select = 1              " Close when something's selected
"let Tlist_Use_Right_Window = 1             " Project uses the left window
"let Tlist_File_Fold_Auto_Close = 1         " Close folds for inactive files

" }}}

" {{{ ctrlp (plugin: https://github.com/kien/ctrlp.vim)

nnoremap <leader>p :CtrlPBuffer<CR>     " keymapping:<leader>p _ctrlp bufferlist
nnoremap <leader>o :CtrlP<CR>           " keymapping:<leader>o _ctrlp open file
nnoremap <silent> <C-o> :CtrlP<CR>      " keymapping:<C-o> _ctrlp open file

" let g:ctrlp_match_window = 'bottom,order:btt,min:1,max:10,results:10'
let g:ctrlp_map = '<c-p>'
let g:ctrlp_cmd = 'CtrlPBuffer'
let g:ctrlp_show_hidden = 1                         " show hidden files
let g:ctrlp_custom_ignore = '\v[\/]\.(git|hg|svn)$' " ignore paths
let g:ctrlp_reuse_window = 'netrw\|help\|quickfix'  " reuse windows
let g:ctrlp_clear_cache_on_exit = 1                 " don't reuse cache
let g:ctrlp_cache_dir = $HOME.'/.vim/tmp/ctrlp'     " ctrlp cache dir
let g:ctrlp_max_history = &history                  "
let g:ctrlp_follow_symlinks = 1                     " follow symlinks
let g:ctrlp_regexp_search = 1                       " regex search by default
let g:ctrlp_max_height = 15                         " height 15

" }}}

" {{{ UltiSnips (plugin: https://github.com/SirVer/ultisnips.git)

let g:UltiSnipsSnippetsDir = expand("$HOME/.vim/snippets/")
let g:UltiSnipsEditSplit = "vertical"   " split window vertical
let g:UltiSnipsUsePythonVersion = 2     " use python 2/3

" ultisnips mappings
let g:UltiSnipsExpandTrigger="<s-tab>"
let g:UltiSnipsJumpForwardTrigger="<s-tab>"
"let g:UltiSnipsJumpBackwardTrigger="<c-tab>"
"unlet g:UltiSnipsListSnippets
"unlet g:UltiSnipsJumpBackwardTrigger

" filetype overwrites
"let g:UltiSnipsAddFiletypes html.css
"let g:UltiSnipsAddFiletypes php.html

" }}}

" {{{ completion / supertab (plugin: todo)

set omnifunc=syntaxcomplete#Complete

" }}}

" {{{ syntastic

let g:syntastic_check_on_open=1
let g:syntastic_check_on_wq=0
let g:syntastic_auto_loc_list=2
let g:syntastic_always_populate_loc_list=1
let g:syntastic_enable_signs=1
let g:syntastic_auto_jump=1
let g:syntastic_error_symbol = '✗'
let g:syntastic_warning_symbol = '!'
"let g:syntastic_disabled_filetypes=['html']

let g:syntastic_stl_format = '[%E{Err: %fe #%e}%B{, }%W{Warn: %fw #%w}]'

" }}}

" {{{ Python

autocmd FileType python set omnifunc=pythoncomplete#Complete

""" syntastic
let g:syntastic_python_checkers=['flake8']
let g:syntastic_python_flake8_args='--ignore=E501'  " E501 - long lines

" }}}

" {{{ php

autocmd FileType php set omnifunc=phpcomplete#CompletePHP
autocmd FileType php let php_sql_query=1
autocmd FileType php let php_htmlInStrings=1

""" syntastic
let g:syntastic_php_checkers=['php','phpcs']
let g:syntastic_php_phpcs_args='--standard=/home/simon/.vim/helper/phpcs_ruleset.xml'

" Map <CTRL>-P to run PHP parser check
"autocmd FileType php noremap <C-P> :!php -l %<CR>

" The php completion dictionary is provided by Rasmus: http://lerdorf.com/funclist.txt
"autocmd FileType php set dictionary-=/home/simon/.vim/documentation/php_funclist.txt dictionary+=/home/simon/.vim/documentation/php_funclist.txt

" php manual
"function! OpenPhpFunction (keyword)
"    let proc_keyword = substitute(a:keyword , '_', '-', 'g')
"    exe 'split'
"    exe 'enew'
"    exe "set buftype=nofile"
"    exe 'silent r!lynx -dump -nolist http://www.php.net/manual/en/print/function.'.proc_keyword.'.php'
"    exe 'norm gg'
"    exe 'call search ("' . a:keyword .'")'
"    exe 'norm dgg'
"    exe 'call search("User Contributed Notes")'
"    exe 'norm dGgg'
"endfunction
"autocmd FileType php noremap <C-k> :call OpenPhpFunction('<C-r><C-w>')<CR>

" }}}

" {{{ javascript

autocmd FileType javascript set omnifunc=javascriptcomplete#CompleteJS

""" fix html tidy for angular sytax
let g:syntastic_html_tidy_ignore_errors=[" proprietary attribute \"ng-"]

""" syntastic
let g:syntastic_javascript_gjslint_args='--max_line_length=120'
"let g:syntastic_javascript_checkers = ['gjslint']
"let g:syntastic_javascript_checkers = ['jshint'];

" }}}

" {{{ html/css

autocmd FileType html set omnifunc=htmlcomplete#CompleteTags
autocmd FileType css set omnifunc=csscomplete#CompleteCSS

" }}}

" {{{ xml

autocmd FileType xml set omnifunc=xmlcomplete#CompleteTags

" }}}

" {{{ sql

let g:sql_type_default = 'pgsql'

" }}}

" {{{ shell / bash

"autocmd FileType sh set foldcolumn=2 foldminlines=5 foldlevelstart=1
"autocmd FileType sh let sh_fold_enabled=3
"autocmd FileType sh set foldmethod=syntax

let g:is_bash=1

" }}}

" {{{ C

autocmd FileType c set omnifunc=ccomplete#Complete

" }}}

" {{{ make

autocmd FileType make set noexpandtab shiftwidth=8

" }}}

" {{{ binary

"augroup Binary au! au BufReadPre *.bin let &bin=1 au BufReadPost *.bin if &bin | %!xxd au BufReadPost  *.bin set filetype=xxd | endif au BufWritePre *.bin if &bin | %!xxd -r au BufWritePre *.bin endif au BufWritePost *.bin if &bin | %!xxd au BufWritePost *.bin set nomod | endif

" }}}

" {{{ gvim

if has('gui_running')
    set guioptions-=T       " no toolbar
    set guioptions-=m       " no menubar
    set guioptions-=r       " no right scrollbar
    set guioptions-=L       " no left scrollbar
endif

" }}}

" {{{ vimrc

""" edit vimrc
nmap <silent> <leader>ve :e $MYVIMRC<CR>    " keymapping:<leader>ve _edit vimrc

""" reload vimrc
nmap <silent> <leader>vr :so $MYVIMRC<CR>   " keymapping:<leader>vr _reload vimrc

""" auto-reload vimrc on save
"autocmd BufWritePost .vimrc source ~/.vimrc
"autocmd BufWritePost vimrc source ~/.vimrc


" }}}

""" other references
" bracketed-paste (plugin: https://github.com/ConradIrwin/vim-bracketed-paste)

