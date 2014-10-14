simons vim config
=============

#### With this config I fight my daily battle as a developer.

This repo includes my vim configs, a collection of plugins as submodules, a bunch of color themes, ...  If you like to nurse and groom your vim config, like me - I'm pretty sure you will find a few nice snippits here.

If you have nice tips or a few lines of cool config for me, please write a mail to <simon.codingmonkey@googlemail.com>. 

## Overview

[TOC]

## Repositories

* GitHub:
    * https://github.com/simonschiele/dot.vim/
    * git://github.com/simonschiele/dot.vim.git

* Self Hosted:
    * git@simon.psaux.de:dot.vim.git  (just [ask](mailto:simon.codingmonkey@googlemail.com) for write access)
    * http://simon.psaux.de/git/dot.vim.git/


## Repo Content

```
/
|
|_ colors/          color schemes
|
|_ documentation/   readmes, plugin docs, ...
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


 # To add another plugin as subrepo, just use something like this:  
 `> git submodule add https://github.com/vim/blub.git plugins/blub`


## Keymappings
    
    # modifiers notation
    ,                   - <Leader>
    Strg/Ctrl           - <C>
    Shift               - <S>
    Enter               - <CR>

    # files
    <Leader>o           - open file (command-t)

    # buffers
    <Leader>b           - buffer overview (command-t)

    # folding
    <Leader>f           - toggle folding under cursor
    <Leader><S>+f       - toggle all folding

    # undo
    <Leader>u           - toggle Gundo

    # navigation (mostly cmd mode)
    I                   - Jump to start of line and switch to insert mode
    $                   - Go to end of the line.
    J                   - Join lines
    gg                  - Jump to beginning of file
    G                   - Jump to end of file
    :<line>             - Jump to line
    <C> + f/b           - Page down/back scroll.

    # edit
    <Leader>ci          - toggle commenting (nerdcommenter)
    <Leader>cc          - comment (nerdcommenter)
    <Leader>cu          - uncomment (nerdcommenter)
    gUU / guu           - uppercase / lowercase line
    gUiw                - current word to uppercase
    3~                  - toggle case of next three characters
    g~3w                - toggle case of next three words
    g~iw                - toggle case of the current word
    df, / dF,           - delete all characters till ',' before/after cursor

    # helpers
    F2                  - toggle paste
    F3                  - toggle search highlite
    F4                  - toggle ignorecase
    F5                  - syntax/parser check
    <S>+F5              - exec
    F6                  - Gundo
    F7                  - language / spell check
    F8                  - file browser (nerdtree)
    F9                  - tagbar
    F10                 - scrollsync
    

## included plugins
    
    sorry, this listing is not up-to-date anymore...
    
    * "pathogen" (https://github.com/tpope/vim-pathogen.git)
          Description: Plugin-Manager

    * "command-t" (https://github.com/wincent/Command-T)
          Description: fast/intuitive file opening and buffer switching
          Installation: cd ~/.vim/plugins/command-t/ && rake make
          Depends: ruby + vim with ruby support

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

    * "vim-fugitive" (https://github.com/tpope/vim-fugitive)
          Description: awesome git plugin

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


## included color schemes
    
    sorry, this listing is not up-to-date anymore...

    * 256-jungle (Piotr Husiatyński <phusiatynski@gmail.com>)  
    * adrian (Adrian Nagle <vim@naglenet.org>) (state 25 Sep 2001)  
    * calmar256-dark (calmar <mac@calmar.ws>) (state 02 March 2007)  
    * colorful256 (Jagpreet <jagpreetc AT gmail DOT com>) (state 03 Oct 2007)  
    * desert256 (Henry So, Jr. <henryso@panix.com>)  
    * desert (Hans Fugal <hans@fugal.net>) (state 2003/06/02)  
    * deveiate (Mahlon E. Smith <mahlon@martini.nu> & Michael Granger   <ged@faeriemud.org>) (state 27 Jun 2008)  
    * inkpot (Ciaran McCreesh <ciaran.mccreesh@googlemail.com>)  
    * liquidcarbon (Jeet Sukumaran) (state 06 October 2010)  
    * wombat256 (David Liang <bmdavll at gmail dot com>) (state November 28 2008)  
    * xoria256 (Dmitriy Y. Zotikov (xio) <xio@ungrund.org>)   
    * lucius (Jonathan Filip <jfilip1024@gmail.com>) (state 13 July 2013)  
    * Smyck (John-Paul Bader) (state 13 July 2013)  


## License

This repo contains mostly work from other very gifted people - of course the license of their plugins/schemes is not changed or anything.

Code in this repo that was written by me:  
[MIT License](http://opensource.org/licenses/MIT)


## Authors
                                        
**Simon Schiele**

* http://simon.psaux.de/
* [simon.codingmonkey@googlemail.com](mailto:simon.codingmonkey@googlemail.com)

