
" {{{ Pathogen

" Use pathogen to load further modules from plugins/
filetype off
runtime plugins/pathogen/autoload/pathogen.vim
call pathogen#infect('plugins/{}')
call pathogen#helptags()

" }}}

" {{{ Look / Colors / Sounds

""" enable highliting
if has("syntax")
    syntax on
endif

""" colorcount stuff deactivated at the moment. crappy idea...
"if $COLORCOUNT == "" || $COLORCOUNT == "256"
    "set t_Co=256
    "color wombat256
"else
    "color wombat
"endif

set ttimeoutlen=50
set synmaxcol=0     " process highliting without char limit 
" set synmaxcol=1000 " process highliting on lines <= 1000 chars 

set t_Co=256
set background=dark
"set list           " show unprintable chars

"let g:solarized_bold=1
"let g:solarized_italic=1
"let g:solarized_underline=0
let g:solarized_contrast='high'
let g:solarized_visibility='low'
let g:solarized_termtrans=1
let g:solarized_termcolors=16
"let g:solarized_termcolors=256

colorscheme solarized

""" fancy cursor-crosshair
augroup CursorLine
    au!
    au VimEnter,WinEnter,BufWinEnter * setlocal cursorline
    au VimEnter,WinEnter,BufWinEnter * setlocal cursorcolumn
    au WinLeave * setlocal nocursorline
    au WinLeave * setlocal nocursorcolumn
augroup END

""" hi overwrite
"hi normal   ctermfg=white  ctermbg=black guifg=white  guibg=black
"hi nontext  ctermfg=blue   ctermbg=black guifg=blue   guibg=black

""" line numbering
set number

""" statusline
set laststatus=2

""" Not really used, since power-/airline...
set statusline=[%n]%y[%{strlen(&fenc)?&fenc:'none'}][%{&ff}]%r%h%w%m%=%1*%F%*\ [line\ %l/%L\|%p%%\|char\ %v]

""" disable extended UI on gvim
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

" Add a bit extra margin to the left
" set foldcolumn=1

""" folding
" foldmethods:
" marker    - folding on three '{'
" syntax    - folding by syntax-highliting
" indent    - folding by indent
" diff      - folding on unchanged lines
set foldmethod=marker

""" autofold
"set foldclose=all      " autoclose folding on leaving
"set foldopen=all       " autoopen fold on cursor

""" brackets
set matchpairs+=<:> " add < > to chars that form pairs (see % command)
set matchtime=1 " show matching brackets quicker than default
set showmatch

""" mouse
"set mouse=a|b          " To play with x11 integration - confusing x11 behavier...

""" save/load
set autoread
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
set history=1000        " keep 1000 lines of command line history
set undolevels=500      " 500 undos
set undoreload=10000    " number of lines to save for undo
set undodir=~/.vim/tmp/undo
set undofile

" Tell vim to remember certain things when we exit
" "  '10  :  marks will be remembered for up to 10 previously edited files
" "  "100 :  will save up to 100 lines for each register
" "  :20  :  up to 20 lines of command-line history will be remembered
" "  %    :  saves and restores the buffer list
" "  n... :  where to save the viminfo files
" " set viminfo='10,\"100,:20,%,n~/.viminfo'
set viminfo='20,\"10000 " read/write a .viminfo file  """

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

set browsedir=buffer    " open path should be on pwd of file in buffer

"" automatically give executable permissions if file begins with #! and contains '/bin/' in the path
"au BufWritePost * if getline(1) =~ "^#!" | if getline(1) =~ "/bin/" | silent !chmod a+x <afile> | endif | endif

"" auto-reload vimrc on save
"autocmd BufWritePost .vimrc source ~/.vimrc
"autocmd BufWritePost vimrc source ~/.vimrc

"" strange settings for split windows. they are always minimized to
"" one line, except one. and you can switch nicely... not usable for
"" me but maybe comes handy some day for devices with small screen...
"set winminheight=0
"set winheight=999

"" don't lose selection after doing indents
"vnoremap > >gv
"vnoremap < <gv

""" navigation
" set scrolloff=3                     " min 3 lines above/below cursor while scrolling
set scrolloff=999                     " cursor centered

""" input
set backspace=indent,eol,start      " more intuitive backspacing in insert mode

" }}}

" {{{ Keymappings & Plugin Settings

""" Set a more intuitive <Leader>
let mapleader = ","
let g:mapleader = ","

" Fast saving
nmap <leader>w :w!<cr>

""" firefox-like navigation
nnoremap <silent> <C-PageDown> :bn<CR>
nnoremap <silent> <C-PageUp> :bp<CR>
nnoremap <silent> <C-q> :bn<CR>

""" w!! to save as sudo
cmap w!! w !sudo tee % >/dev/null

""" disable recording
map q <Nop>

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
let g:tagbar_usearrows = 1
let g:tagbar_phpctags_bin='/home/simon/.lib/phpctags/phpctags'

""" scrollsync
map <F10> :set scb!<bar>set scb?<cr>

""" [plugin] Snipmate
let g:snips_dir = "~/.vim/snippets/"
let g:snips_author = 'Simon Schiele'
"let g:snips_trigger_key_backwards='<none>'

""" [plugin] vim-ack
let g:ackprg="ack-grep -H --nocolor --nogroup --column"
nmap <leader>g :Ack 

""" [plugin] excel.vim
let g:zipPlugin_ext = '*.zip,*.jar,*.xpi,*.ja,*.war,*.ear,*.celzip,*.oxt,*.kmz,*.wsz,*.xap,*.docx,*.docm,*.dotx,*.dotm,*.potx,*.potm,*.ppsx,*.ppsm,*.pptx,*.pptm,*.ppam,*.sldx,*.thmx,*.crtx,*.vdw,*.glox,*.gcsx,*.gqsx'

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

""" [plugin] syntastic
" also have a look at the 'Language Support' section for language specific options 
let g:syntastic_check_on_open=1
let g:syntastic_check_on_wq=0
let g:syntastic_auto_loc_list=2
let g:syntastic_always_populate_loc_list=1
let g:syntastic_disabled_filetypes=['html']
let g:syntastic_enable_signs=1

"if has("unix")
  "let g:syntastic_error_symbol = "█"
  "let g:syntastic_style_error_symbol = ">"
  "let g:syntastic_warning_symbol = "█"
  "let g:syntastic_style_warning_symbol = ">"
"else
  "let g:syntastic_error_symbol = "X"
  "let g:syntastic_style_error_symbol = ">"
  "let g:syntastic_warning_symbol = "!"
  "let g:syntastic_style_warning_symbol = ">"
"endif

"nnoremap <silent> <C-d> :lclose<CR>:bdelete<CR>     " location list close
"cabbrev <silent> bd lclose\|bdelete


""" [plugin] airline
" themes: badwolf, base16, bubblegum, dark, hybrid, jellybeans, kalisi, kolor,
" laederon, light, lucius, luna, molokai, monochrome, murmur, powerlineish,
" raven, serene, silver, simple, solarized, sol, tomorrow, ubaryd,
" understated, wombat, zenburn

" :AirlineToggleWhitespace 
" :AirlineToggle 

"let g:bufferline_echo =
let g:airline_powerline_fonts=1
let g:airline_theme='base16'
"let g:airline_theme=
let g:airline_detect_paste=1
let g:airline_detect_modified=1
let g:airline_detect_iminsert=1

" control which sections get truncated and at what width.
"let g:airline#extensions#default#section_truncate_width = {
"      \ 'b': 90,
"      \ 'y': 90,
"      \ })

let g:airline_inactive_collapse=1      " inactive windows have only filename
let g:airline_exclude_preview=0        " no airline in preview_window
"let g:airline_exclude_filetypes=[]    " filetypes which have no airline
"let g:airline_exclude_filenames=[]    " same for filenames 

let g:airline#extensions#tagbar#enabled=1           " tagbar
let g:airline#extensions#tabline#enabled=1          " display open buffers in tabline

" airline->git
let g:airline_enable_fugitive=1
let g:airline#extensions#branch#enabled=1          " 
let g:airline#extensions#branch#empty_message = ''
let g:airline#extensions#hunks#enabled=1            " enable/disable showing a summary of changed hunks under source control
let g:airline#extensions#hunks#non_zero_only = 0    " enable/disable showing only non-zero hunks
"let g:airline#extensions#hunks#hunk_symbols = ['+', '~', '-']

" csv
let g:airline#extensions#csv#enabled=1      " csv.vim
let g:airline#extensions#csv#column_display = 'Number' " (default)
let g:airline#extensions#csv#column_display = 'Name'

" syntastic
let g:airline_enable_syntastic=1
let g:airline#extensions#syntastic#enabled=1        " syntastic

" airline->whitespace
let g:airline#extensions#whitespace#enabled=1
"let g:airline#extensions#whitespace#symbol = '!'
"let g:airline#extensions#whitespace#checks = [ 'indent', 'trailing' ]

" airline->whitespace->message
let g:airline#extensions#whitespace#show_message = 1
let g:airline#extensions#whitespace#trailing_format = 'trailing[%s]'
let g:airline#extensions#whitespace#mixed_indent_format = 'mixed-indent[%s]'

" ctrlp <https://github.com/kien/ctrlp.vim>
nnoremap <leader>p :CtrlPBuffer<CR>
nnoremap <leader>o :CtrlP<CR>
nnoremap <silent> <C-o> :CtrlP<CR>

let g:airline#extensions#ctrlp#color_template = 'insert' " (default)
"let g:airline#extensions#ctrlp#color_template = 'normal'
"let g:airline#extensions#ctrlp#color_template = 'visual'
"let g:airline#extensions#ctrlp#color_template = 'replace'

let g:ctrlp_map = '<c-p>'
let g:ctrlp_cmd = 'CtrlPBuffer'
let g:ctrlp_custom_ignore = '\v[\/]\.(git|hg|svn)$'
let g:ctrlp_show_hidden = 1
"let g:ctrlp_match_window = 'bottom,order:btt,min:1,max:10,results:10'
let g:ctrlp_reuse_window = 'netrw\|help\|quickfix'
let g:ctrlp_clear_cache_on_exit = 1
let g:ctrlp_cache_dir = $HOME.'/.vim/tmp/ctrlp'
let g:ctrlp_max_history = &history
let g:ctrlp_follow_symlinks = 1
let g:ctrlp_regexp_search = 1       " Regex search by default
let g:ctrlp_max_height = 15         " Show more results at once

" virtualenv <https://github.com/jmcantrell/vim-virtualenv>
"let g:airline#extensions#virtualenv#enabled = 1  " enable/disable virtualenv integration >

" airline symbols
"if !exists('g:airline_symbols')
"    let g:airline_symbols = {}
"endif

" unicode symbols
"let g:airline_left_sep = ''
"let g:airline_left_alt_sep = ''
"let g:airline_right_sep = ''
"let g:airline_right_alt_sep = ''
"let g:airline#extensions#branch#symbol = ' '
"let g:airline#extensions#readonly#symbol = ''
"let g:airline_linecolumn_prefix = ' '
"let g:airline_left_sep='»'
"let g:airline_left_sep='▶'
"let g:airline_right_sep='«'
"let g:airline_right_sep='◀'
"let g:airline_symbols.linenr='␊'
"let g:airline_symbols.linenr='␤'
"let g:airline_symbols.linenr='¶'
"let g:airline_symbols.branch='⎇'
"let g:airline_symbols.paste='ρ'
"let g:airline_symbols.paste='Þ'
"let g:airline_symbols.paste='∥'
"let g:airline_symbols.whitespace='Ξ'

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
let g:syntastic_python_checkers=['flake8']
let g:syntastic_python_flake8_args='--ignore=E501'

" Add the virtualenv's site-packages to vim path
py << EOF
import os.path
import sys
import vim
if 'VIRTUAL_ENV' in os.environ:
    project_base_dir = os.environ['VIRTUAL_ENV']
    sys.path.insert(0, project_base_dir)
    activate_this = os.path.join(project_base_dir, 'bin/activate_this.py')
    execfile(activate_this, dict(__file__=activate_this))
EOF


""" C
autocmd FileType c set omnifunc=ccomplete#Complete

""" make
autocmd FileType make set noexpandtab shiftwidth=8

""" sql
let g:sql_type_default = 'pgsql'

""" sh
"let g:is_bash = 1
"let g:sh_fold_enabled=3     " (enable function folding)folding

""" binary
"augroup Binary au! au BufReadPre *.bin let &bin=1 au BufReadPost *.bin if &bin | %!xxd au BufReadPost  *.bin set filetype=xxd | endif au BufWritePre *.bin if &bin | %!xxd -r au BufWritePre *.bin endif au BufWritePost *.bin if &bin | %!xxd au BufWritePost *.bin set nomod | endif

" }}}

" netrw
let g:netrw_altv           = 1
let g:netrw_fastbrowse     = 2
let g:netrw_keepdir        = 0
let g:netrw_liststyle      = 2
let g:netrw_retmap         = 1
let g:netrw_silent         = 1
let g:netrw_special_syntax = 1

" some kind of highliting
let readline_has_bash = 1

" Buffer command
command -nargs=? -bang B if <q-args> != '' | exe 'buffer '.<q-args> | else | ls<bang> | let buffer_nn=input('Which one: ') | if buffer_nn != '' | exe buffer_nn != 0 ? 'buffer '.buffer_nn : 'enew' | endif | endif


" ruler
"set ruler 

" backwards highliting
"let sh_minlines = 50 
"let sh_maxlines = 100       " default 2x sh_minlines
"let ptcap_minlines = 50
"let rexx_minlines = 50

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

"let g:SuperTabCrClosePreview = 1
"let g:SuperTabClosePreviewOnPopupClose = 1

"let g:SuperTabMappingForward = '<s-tab>'
"let g:SuperTabMappingBackward = '<s-c-tab>'
"let g:SuperTabMappingTabLiteral = '<tab>'

"autocmd FileType *
  "\ if &omnifunc != '' |
  "\   call SuperTabChain(&omnifunc, "<c-p>") |
  "\   call SuperTabSetDefaultCompletionType("<c-x><c-u>") |
  "\ endif

"set completeopt=longest,menuone

""" random stuff
"
" set fillchars=vert:┃,diff:⎼,fold:⎼  " it's about borders?!

" set printoptions=paper:a4
"set printoptions=number:y " put line numbers on hardcopy

" if $POWERLINE_FONT == "true" 
" endif

" set binary " show control characters (ignore 'fileformat')

" " swap aus
"
" set noautoindent " do not auto indent
"
"

"command Shell :set nolist | ConqueTermSplit bash
"command PythonShell :set nolist | ConqueTermSplit python

"set foldmethod=syntax
"set foldlevelstart=1

"let javaScript_fold=1         " JavaScript
"let perl_fold=1               " Perl
"let php_folding=1             " PHP
"let r_syntax_folding=1        " R
"let ruby_fold=1               " Ruby
"let sh_fold_enabled=1         " sh
"let vimsyn_folding='af'       " Vim script
"let xml_syntax_folding=1      " XML

" set foldmethod=indent
" set foldnestmax=2

" let g:is_bash = 1
" let g:sh_fold_enabled = 1

" ciw !!!

" -- tags
"set tags=tags;$HOME/.vim/tags/ "recursively searches directory for 'tags' file

" TagList Plugin Configuration
"let Tlist_Ctags_Cmd='/usr/bin/ctags'       " point taglist to ctags
"let Tlist_GainFocus_On_ToggleOpen = 1      " Focus on the taglist when its  toggled
"let Tlist_Close_On_Select = 1              " Close when something's selected
"let Tlist_Use_Right_Window = 1             " Project uses the left window
"let Tlist_File_Fold_Auto_Close = 1         " Close folds for inactive files

"--ENABLE PYTHON/DJANGO OMNICOMPLETE
"
"filetype plugin on
"autocmd FileType python set omnifunc=pythoncomplete#Complete
"autocmd FileType javascript set omnifunc=javascriptcomplete#CompleteJS
"autocmd FileType html set omnifunc=htmlcomplete#CompleteTags
"autocmd FileType css set omnifunc=csscomplete#CompleteCSS
"autocmd FileType xml set omnifunc=xmlcomplete#CompleteTags
"autocmd FileType php set omnifunc=phpcomplete#CompletePHP
"autocmd FileType c set omnifunc=ccomplete#Complete

"set omnifunc=syntaxcomplete#Complete
"autocmd FileType python set omnifunc=pythoncomplete#Complete
"autocmd FileType javascript set omnifunc=javascriptcomplete#CompleteJS
"autocmd FileType html set omnifunc=htmlcomplete#CompleteTags
"autocmd FileType css set omnifunc=csscomplete#CompleteCSS
"
""--SuperTab Integration
"set completeopt-=previewtj
"let g:SuperTabDefaultCompletionType = ""
"let g:SuperTabDefaultCompletionType = "context"

""map <F2> :previous<CR>                  " map F2 to open previous buffer
"map <F3> :next<CR>                      " map F3 to open next buffer
"map <F4> :NERDTreeToggle<CR>            " map F4 to open NERDTree
"map <F5> :TlistToggle<CR>               " map F5 to toggle the Tag Listing
"map <silent><C-Left> <C-T>              " taglist - map Ctrl-LeftArrow to jump to the method/property under your cursor
"map <silent><C-Right> <C-]>             " taglist - map Ctrl-RhitArrow to jump back to your source code
"map <silent><A-Right> :tabnext<CR>      " map Alt-RightArrow to jump to the next tab
"map <silent><A-Left> :tabprevious<CR>   " map Alt-LeftArrow to jump to the previous tab

