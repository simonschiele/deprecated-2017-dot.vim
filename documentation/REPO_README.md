simons vim config
=================

#### With this config I fight my daily battle as a developer.

This repo includes my vim configs, a collection of plugins as submodules, a bunch of color themes, ...  If you like to nurse and groom your vim config, like me - I'm pretty sure you will find a few nice snippits in this config set.

If you have nice tips or a few lines of cool config for me, please write a mail to <simon.codingmonkey@googlemail.com>. 


## Overview

[TOC]


## Repositories

* GitHub:
    * (web) https://github.com/simonschiele/dot.vim/
    * (git) git://github.com/simonschiele/dot.vim.git

* Self Hosted:
    * (web) http://simon.psaux.de/git/dot.vim.git/
    * (git) git@simon.psaux.de:dot.vim.git  (just [ask](mailto:simon.codingmonkey@googlemail.com) for write access)


## Repo Content

```
/
|
|_ colors/          color schemes
|
|_ documentation/   readme, plugin docs, ...
|
|_ helper/          helper for plugins
|
|_ plugins/         plugins
|
|_ spell/           aspell dictionaries for spell check (de, en)
|
|_ tmp/             backup, swap, undo, tmp-files, ...
|
|_ vimrc-bigfile    special vim config for very big files (tested with 1-4gb files)
|
|_ vimrc            my main vim config
|
\_ README.md        This small help file

```


## Setup / How to use this config

To use this configuration, just checkout repo + subrepos and link vimrc directly to your home:

```
 # Backup existing config
 `> mv ~/.vim/ ~/vim-old/`
 `> mv ~/.vimrc ~/vim-old/dot.vimrc`

 # Clone base repo  
 `> git clone <repo> ~/.vim/`  

 # Clone subrepos (plugins)  
 `> cd ~/.vim/`  
 `> git submodule update --init --recursive`  

 # Link vimrc to your HOME   
 `> cd ~/`   
 `> ln -s ~/.vim/vimrc ~/.vimrc`

```


## Extent this config set

```
 # To add another plugin as subrepo, just use something like this:
 `> git submodule add https://github.com/developer/vim-cool-plugin.git plugins/cool`

```

## Use vim (and this config)

### Documentation
    * learn vim the hard way
    * [Learn Vimscript the Hard Way](http://learnvimscriptthehardway.stevelosh.com/ "[ebook] Steve Losh - 2013 - Learn Vimscript the Hard Way") by [Steve Losh](https://github.com/sjl "[githuub] sjl (Steve Losh)")


### vim command line arguments
    
    vim -O <file(s)>    - open <file(s)> in vertical split
    vim -o <file(s)>    - open <file(s)> in horizontal split
    vim -r <file>       - open last version of <file> after crash
    vim +<n> <file>     - open <file> on line <n>
    vim + <file>        - open <file> on end of file
    vim +/<pattern>     - open <file> on first occurance of <pattern>

### Keymappings
    
    # modifiers
    <Leader>            - , (comma) 
    <C>                 - Strg/Ctrl
    <S>                 - Shift
    <CR>                - Enter
    <ESC>               - Esc
    <Ins>               - Einfg/Insert 
    
    # actions 
    [~Visual~]          - Do some visual selection 
    [~Motion~]          - Move in a direction
    [~Edit~]            - Edit something

    # descriptions
    <param>             - mandatory parameter
    [param]             - optional parameter
    
    (plugin: <name>)    - mapping is from the named plugin
    
    (custom)            - this mapping is only available in this custom config
    !(custom)           - this mapping is removed in this conifg but it's
                          available in a default vim setup

#### navigation
    i                   - switch to insert mode at cursor
    I                   - jump to start of line and switch to insert mode
    R                   - switch to replace mode
    r                   - replace mode for a single character 
    <Ins>               - Toggle between insert & replace mode
    <Esc>               - exit insert mode (back to normal/command mode)
    
    0/$                 - Go to start / end of line.
    ^                   - Go to first non-whitespace character
    gg / G              - Jump to beginning / end of file
    :<line>             - Jump to specific line 
    <C> + f/b           - Page down/back scroll.
    M/H/L               - Jump cursor to middle / top / bottom of the screen
    w/b/e               - next word / back word / end word (by punctuation) 
    W/B/E               - next word / back word / end word (by spaces) 
    <C> + F/B           - forward / backwards full screen
    <C> + D/U           - down / up half a screen
    <C> + E/Y           - scroll one line up / down
    '.                  - go back to position of the last edit
    ''                  - go back to position before jump
    %                   - go to matching bracket
    { / }               - last / next blank line (by paragraph)
    gd                  - go to definition of local symbol under cursor (<C>+O returns)
    <C> + ]             - jump to definition of global symbol (requires tags file - ^T returns)

#### shortcuts
    F3                  - deactive the current search highlite (custom)
    F4                  - toggle ignorecase for search (custom) 
    F7                  - language / spell check (custom) 
    F8                  - file browser (custom) (plugin: nerdtree) 
    F9                  - tagbar (custom) (plugin: tagbar)

#### visual mode
    v       - visual mode selects range of text
    V       - visual line mode - selects entire lines 
    ctrl-v  - visual block mode - selects columns
    gv      - select previous block
    
    [~Visual~]I [~Edit~] <ESC>    - multi edit 

#### windows
    <C> + w  ⇦ / ⇩ / ⇧ / ⇨      - focus window left/down/up/right of active window
    <C> + w  h / j / k / l      - go to window left/down/up/right of active one
    <C> + w  H / J / K / L      - move window to left/bottom/top/right 
    <C> + w [number] +/-        - resize window horizontally
    <C> + w [number] </>        - resize window vertically
    <C> + w <C> + w             - next window (cycle)
    <C> + w n                   - new window
    <C> + w v                   - split vertically 
    <C> + w s                   - split horizontally
    :only / <C> + o             - close all but active window
    :hide                       - close active window

#### files & buffer 
    <C> + o             - open file (custom) (plugin: ctrlP)
    <C> + p             - buffer overview (custom) (plugin: ctrlP)
    :B                  - ghetto-failover bufferlist (custom)
    :e <file>           - open <file>
    :r <file>           - read <file> and append after this line
    :w [filename]       - save (optional save with new <filename>)
    ZZ / :x             - save & exit
    :q                  - exit if no changes
    :q!                 - exit and don't save changes
    :w!!                - save with sudo (custom)

#### editing
    .                   - repeat last edit
    <C> + t / d         - indent current line forward/backwards (in insert mode)
    [~Visual~] + > / <  - indent selected block
    >> / <<             - indent current line forward/backwards
    df, / dF,           - delete all characters till ',' before/after cursor
    gUU / guu           - upper- / lowercase complete line
    gUiw / guiw         - current word to upper- / lowercase
    3~                  - toggle case of next three characters
    g~3w                - toggle case of next three words
    g~iw                - toggle case of the current word
    [~Visual~] + J      - Join selected line(s)
    [n]J                - Join next [n] lines to the current one 
    a / A               - append text after cursor / end of line and switch to insert mode
    o / O               - new line below / above and switch to insert mode
    d[n]w / d[n]d       - delete [n] word(s) / [n] line(s) including the one under the cursor
    [n]D                - delete to end of line + [n] following line(s) 
    ciw                 - delete word under cursor and jump into insert mode 
    dib                 - delete everything inside of brackets / parentheses 
    d[n]w / d[n]b       - deletes next / previous [n] words/ 
    :<x>,<y>d           - deletes from line <x> to line <y>
    d[~Motion~]         - deletes in the direction of the motion

#### search / jump
    /<pattern>          - find forward 
    ?<pattern>          - find backward 
    n / <S> + n         - repeat search (jump to next match) / reverse repeat search
    * / #               - jump to next / last occurrence of the word under the cursor
    g* / g#             - jump to next / last partial of the word under cursor
    [I                  - list lines with matching word under cursor in split

#### replacing
 
    # basic replacement
    :s/<pattern1>/[pattern2]/flag

    # flags
    g  -   replace all occurrences of pattern1
    c  -   confirm replaces
    &  -   repeat last :s command

#### folding
    <Leader>f           - toggle folding under cursor (custom)
    <Leader><S>+f       - toggle all folding (custom)

#### commenting
    <Leader>ci          - toggle commenting (custom) (plugin: nerdcommenter)
    <Leader>cc          - comment (custom) (plugin: nerdcommenter)
    <Leader>cu          - uncomment (custom) (plugin: nerdcommenter)

#### completion
    <C> + n             - automatic word completion (in insert mode)


### vim lingua - learn to speak vim

(source: http://yanpritzker.com/2011/12/16/learn-to-speak-vim-verbs-nouns-and-modifiers/)

"Using vim is like talking to your editor in 'verb modifier object' sentences, turned into acronyms [...] don’t try to do anything by pressing keys many times, instead speak to the editor in sentences"

verbs: 
    * v (visual)
    * c (change)
    * d (delete)
    * y (yank/copy)

modifiers:
    * i (inside)
    * a (around)
    * t (till .. finds a character)
    * f (find .. like till except including the char)
    * / (search .. find a string/regex)

nouns / text objects:
    * w (word)
    * s (sentence)
    * p (paragraph)
    * b (block/parentheses)
    * t (tag, works for html/xml)

from plugins:
    * s / S ([noun] surround (plugin: vim-surround))

Examples: 
 delete the current word: diw (delete inside word)
 change current sentence: cis (change inside sentence)
 change a string inside quotes: ci” (change inside quote)
 change until next occurrence of ‘foo’: c/foo (change search foo)
 change everything from here to the letter X: ctX
 visually select this paragraph: vap (visual around paragraph)

Examples from plugins:
 (plugin: surround) visually select a word and surround it with quotes: viwS”
 (plugin: surround) change surround from single quote to double quote: cs’”


## Thirdparty subrepos

### plugins
    
    * "pathogen" (https://github.com/tpope/vim-pathogen.git)
          Description: Plugin-Manager

    * "vim-fugitive" (https://github.com/tpope/vim-fugitive)
          Description: awesome git plugin
    
    
    sorry, this listing is not up-to-date anymore...

    
    * "ack" (https://github.com/mileszs/ack.vim)
          Description: better than grep :-)
          Depends: ack-grep

    * "gundo" (https://github.com/sjl/gundo.vim)
          Description: visualizing the undo tree
          Depends: vim with python support

    * "vim-surround" (https://github.com/tpope/vim-surround)
          Description: fast editing of surroundings

    * "Mark" (https://github.com/vim-scripts/Mark)
          Description: marks several keywords/regex in different colors

    * "nerdcommenter" (https://github.com/scrooloose/nerdcommenter)
          Description: comfortable commenting

    * "nerdtree" (https://github.com/scrooloose/nerdtree)
          Description: filebrowser

    * "supertab" (https://github.com/ervandew/supertab)
          Description: sane way to handle multiple complete features on <tab>

    * "snipmate" (https://github.com/garbas/snipmate.vim)
          Description: snipmate fork from garbas
          depends: vim-addon-mw-utils, tlib (both plugins are submodules in this repo)
          Comment: put your snippets to ~/.vim/snippets/

    * "tlib_vim" (https://github.com/tomtom/tlib_vim)
          Description: "excellent filterable list selection view" for snipmate

    * "vim-addon-mw-utils" (https://github.com/MarcWeber/vim-addon-mw-utils)
          Description: "providing the implementation for caching parsed .snippets files" for snipmate

    * "taglist" by Yegappan Lakshmanan (yegappan AT yahoo DOT com) (state 2007 May 24)
          Description: source browser
          Depends: exuberant-ctags
          Comment: NOT A SUBREPO!

    * "vim-powerline" (https://github.com/Lokaltog/vim-powerline)
          Description: mighty and fancy statusline.
          Depends: patched font! see readme


### color schemes
    
    * 256-jungle (Piotr Husiatyński <phusiatynski@gmail.com>)  
    * adrian (Adrian Nagle <vim@naglenet.org>) (state 25 Sep 2001)  
    * busybee
    * calmar256-dark (calmar <mac@calmar.ws>) (state 02 March 2007)  
    * colorful256 (Jagpreet <jagpreetc AT gmail DOT com>) (state 03 Oct 2007)  
    * desert (Hans Fugal <hans@fugal.net>) (state 2003/06/02)  
    * desert256 (Henry So, Jr. <henryso@panix.com>)  
    * deveiate (Mahlon E. Smith <mahlon@martini.nu> & Michael Granger <ged@faeriemud.org>) (state 27 Jun 2008)  
    * flatlandia
    * github
    * gummybears
    * iawriter
    * inkpot (Ciaran McCreesh <ciaran.mccreesh@googlemail.com>)  
    * jellybeans
    * liquidcarbon (Jeet Sukumaran) (state 06 October 2010)  
    * lucius (Jonathan Filip <jfilip1024@gmail.com>) (state 13 July 2013)  
    * railscasts
    * smyck (John-Paul Bader) (state 13 July 2013)  
    * solarized
    * wombat
    * wombat256 (David Liang <bmdavll at gmail dot com>) (state November 28 2008)  
    * xoria256 (Dmitriy Y. Zotikov (xio) <xio@ungrund.org>)   


## tools

 # List all color schemes in repo
 `grep "colors_name\ \?=\ \?[\"']" ~/.vim/ -r | cut -f'2-' -d'=' | sed "s/[\"\ \']//g" | sort -u`

 # List all plugin-urls in vimrc
 `grep -oi "(plugin[^)]*)" ~/.vimrc | cut -f2- -d' ' | sed 's/)$//g'`


## License

Code in this repo that was written by me:  
[MIT License](http://opensource.org/licenses/MIT)

This repo contains many plugins/schemes from other very gifted people. Of course the original license of their plugins/schemes is not touched or changed.


## Authors
                                        
**Simon Schiele**

* http://simon.psaux.de/
* [simon.codingmonkey@googlemail.com](mailto:simon.codingmonkey@googlemail.com)

