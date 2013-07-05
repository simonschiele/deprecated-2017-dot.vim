My vim config.
With this config I fight my daily battle as a (web-)developer.
If you have nice tips or snippits for me, just send a mail <simon.codingmonkey@googlemail.com>.

Repo:
 * GitHub:          https://github.com/simonschiele/dot.vim/  (clone git://github.com/simonschiele/dot.vim.git)
 * Self Hosted:     http://simon.psaux.de/git/dot.vim.git/  (clone http://simon.psaux.de/git/dot.vim.git)

If you use this repo as your default configuration, just mail a public key and you will get
write permission to the repo :-)


To use this configuration, just checkout repo + subrepos and link vimrc directly to your home:
 
 # Backup existing config
 > mv ~/.vim/ ~/vim-old/
 > mv ~/.vimrc ~/vim-old/dot.vimrc

 # Clone base repo
 > git clone <repo> ~/.vim/
 
 # Clone subrepos (plugins)
 > cd ~/.vim/
 > git submodule init
 > git submodule update 
 
 # Link vimrc to your HOME 
 > cd ~/
 > ln -s .vim/vimrc ~/.vimrc

 # Build command-t
 > cd ~/.vim/plugins/command-t/
 > ...


To add another plugin as subrepo, just use something like this:
 > git submodule add https://github.com/vim-scripts/The-NERD-Commenter plugins/NerdCommenter


Keymappings:
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

    # helpers
    F2                  - toggle paste
    F3                  - remove highliting until next usage
    F4                  - toggle ignorecase
    F5                  - syntax/parser check
    Shift + F5          - exec
    F6                  - Gundo
    F7                  - language / spell check
    F8                  - file browser
    F9                  - tagbar
    F10                 - scrollsync

    # navigation
    I                   - Jump to start of line and switch to insert mode
    $                   - In command mode, go to end of the line.
    gg                  - Jump tp beginning of file
    G                   - Jump to end of file
    :<line>             - Jump to line (<line> == line number)   
    Ctrl + F/B          - Page down/back scroll.
 
    # edit 
    df, (reverse dF,)   - Delete all characters till , on the current line


included plugins:

    * "pathogen" (https://github.com/tpope/vim-pathogen.git)
          Description: Plugin-Manager

    * "gundo" (https://github.com/sjl/gundo.vim)
          Description: visualizing the undo tree
          Depends: vim with python support

    * "vim-fugitive" (https://github.com/tpope/vim-fugitive)
          Description: awesome git plugin

    * "nerdcommenter" (https://github.com/scrooloose/nerdcommenter)
          Description: comfortable commenting

    * "nerdtree" (https://github.com/scrooloose/nerdtree)
          Description: filebrowser 

    * "supertab" (https://github.com/ervandew/supertab)
          Description: sane way to handle multiple complete features on <tab> 


included color schemes:
    * 256-jungle (Piotr Husiatyński <phusiatynski@gmail.com>)
    * adrian (Adrian Nagle <vim@naglenet.org>) (state 25 Sep 2001)
    * calmar256-dark (calmar <mac@calmar.ws>) (state 02 March 2007)
    * colorful256 (Jagpreet <jagpreetc AT gmail DOT com>) (state 03 Oct 2007)
    * desert256 (Henry So, Jr. <henryso@panix.com>)
    * desert (Hans Fugal <hans@fugal.net>) (state 2003/06/02)
    * deveiate (Mahlon E. Smith <mahlon@martini.nu> & Michael Granger <ged@faeriemud.org>) (state 27 Jun 2008)
    * inkpot (Ciaran McCreesh <ciaran.mccreesh@googlemail.com>)
    * wombat256 (David Liang <bmdavll at gmail dot com>) (state November 28 2008)
    * xoria256 (Dmitriy Y. Zotikov (xio) <xio@ungrund.org>)

