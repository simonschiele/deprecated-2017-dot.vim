My vim config.
With this config I fight my daily battle as a (web-)developer.
If you have nice tips or snipits for me, just send a mail <simon.codingmonkey@googlemail.com>.

Repo:
 * GitHub:          git://github.com/simonschiele/dot.vim.git
 * Self Hosted:     git://psaux.de/dot.vim.git

If you use this repo as your default configuration, just mail a public key and you will get
write permission to the repo :-)


To use this configuration, just checkout repo and link vimrc directly to your home dir:
 > git clone <repo>
 > cd ~/
 > ln -s .vim/vimrc .vimrc
 > git submodule init
 > git submodule update 

To add another plugin as subrepo, just use something like this:
 > git submodule add https://github.com/vim-scripts/The-NERD-Commenter plugins/NerdCommenter

Keymappings / Features:
    F2      - toggle paste
    [...]

included plugins:
    "Taglist" by Yegappan Lakshmanan (yegappan AT yahoo DOT com) (state 2007 May 24)

included subrepos:
	* https://github.com/tpope/vim-pathogen.git
	* https://github.com/tpope/vim-git.git
	* https://github.com/tpope/vim-surround.git
	* https://github.com/msanders/snipmate.vim.git
	* https://github.com/ervandew/supertab.git
	* https://github.com/sontek/minibufexpl.vim.git
	* https://github.com/tpope/vim-fugitive.git
	* https://github.com/wincent/Command-T.git
	* https://github.com/sjl/gundo.vim.git
	* https://github.com/vim-scripts/Mark.git
	* https://github.com/scrooloose/nerdcommenter.git
	* https://github.com/scrooloose/nerdtree.git

included color schemes:
    256-jungle (Piotr Husiatyński <phusiatynski@gmail.com>)
    adrian (Adrian Nagle <vim@naglenet.org>) (state 2001-09-25)
    calmar256-dark (calmar <mac@calmar.ws>) (state 02. March 2007)
    colorful256 (Jagpreet <jagpreetc AT gmail DOT com>) (state 03 Oct, 2007)
    desert256 (Henry So, Jr. <henryso@panix.com>)
    desert (Hans Fugal <hans@fugal.net>) (state 2003/06/02)
    inkpot (Ciaran McCreesh <ciaran.mccreesh@googlemail.com>)
    wombat256 (David Liang <bmdavll at gmail dot com>) (November 28 2008)
    xoria256 (Dmitriy Y. Zotikov (xio) <xio@ungrund.org>)

