(add-to-list 'load-path "~/.emacs.d/common-libs/")
(server-start)
;; Package Management
(load "package")
(package-initialize)
(add-to-list 'package-archives
             '("melpa-stable" . "https://stable.melpa.org/packages/") t)

;; Define default packages
(defvar pankaj/packages '(ac-slime
                          auto-complete
                          autopair
                          cider
                          clojure-mode
                          elpy
                          f
                          feature-mode
                          flycheck
                          graphviz-dot-mode
                          htmlize
                          magit
                          markdown-mode
                          org
                          paredit
                          powerline
			  monokai-theme
                          rvm
                          smex
			  nlinum
			  monokai-theme
			  w3
			  multiple-cursors
                          ubuntu-theme
                          dracula-theme
                          cmake-mode
			  solarized-theme
                          web-mode
			  yasnippet-classic-snippets
			  yasnippet-snippets
			  switch-window
			  ace-window
                          writegood-mode
                          yaml-mode)
  "Default packages")

;; Install default packages
(require 'cl)
(defun pankaj/packages-installed-p ()
  (loop for pkg in pankaj/packages
        when (not (package-installed-p pkg)) do (return nil)
        finally (return t)))

(unless (pankaj/packages-installed-p)
  (message "%s" "Refreshing package database...")
  (package-refresh-contents)
  (dolist (pkg pankaj/packages)
    (when (not (package-installed-p pkg))
      (package-install pkg))))

;;;;;;;;;;;;;;;;;;;;;
;; startup options ;;
;;;;;;;;;;;;;;;;;;;;;

(require 'ido)
(ido-mode t)
(setq ido-enable-flex-matching t
      ido-use-virtual-buffers t)

(setq
 inhibit-splash-screen t
 initial-scratch-message nil)
(scroll-bar-mode -1)
(tool-bar-mode -1)
(menu-bar-mode -1)
(set-default 'cursor-type 'hbar)
(global-hl-line-mode)
(column-number-mode)
(winner-mode t)
(show-paren-mode)
(setq frame-title-format "emacs")

(add-to-list 'auto-mode-alist '("\\.h\\'" . c++-mode))

;; set keys for Apple keyboard, for emacs in OS X
(setq mac-command-modifier 'meta) ; make cmd key do Meta
(setq mac-option-modifier 'super) ; make opt key do Super
(setq mac-control-modifier 'control) ; make Control key do Control
(setq ns-function-modifier 'hyper)  ; make Fn key do Hyper

;; monokai theme
(load-theme 'monokai t)

;; Smex settings
(smex-initialize)
(global-set-key (kbd "M-x") 'smex)
(global-set-key (kbd "M-X") 'smex-major-mode-commands)
;; This is your old M-x
(global-set-key (kbd "C-c C-c M-x") 'execute-extended-command)

;; auto-complete settings
(require 'auto-complete-config)
(ac-config-default)

;; powerline
(require 'powerline)
(powerline-center-theme)

;; framemove
(require 'framemove)
(windmove-default-keybindings)
(setq framemove-hook-into-windmove t)

;; auto pair
(autopair-global-mode)

;; encoding settings
(setq utf-translate-cjk-mode nil)
;; disable CJK coding/encoding (Chinese/Japanese/Korean characters)
(set-language-environment 'utf-8)
(set-keyboard-coding-system 'utf-8-mac)
;; For old Carbon emacs on OS X only
(setq locale-coding-system 'utf-8)
(set-default-coding-systems 'utf-8)
(set-terminal-coding-system 'utf-8)
(unless (eq system-type 'windows-nt)
  (set-selection-coding-system 'utf-8))
(prefer-coding-system 'utf-8)

;; yasnippet settings
(require 'yasnippet)
(yas-global-mode 1)
(define-key yas-minor-mode-map (kbd "<tab>") nil)
(define-key yas-minor-mode-map (kbd "TAB") nil)
(define-key yas-minor-mode-map (kbd "<C-tab>") 'yas-expand)

;; switch windows
(global-set-key (kbd "C-x o") 'switch-window)

;; multiple-cursers
(require 'multiple-cursors)
(global-set-key (kbd "C-S-c C-S-c") 'mc/edit-lines)
(global-set-key (kbd "C->") 'mc/mark-next-like-this)
(global-set-key (kbd "C-<") 'mc/mark-previous-like-this)
(global-set-key (kbd "C-c C-<") 'mc/mark-all-like-this)

;; irony-mode
(add-hook 'c++-mode-hook 'irony-mode)
(add-hook 'c-mode-hook 'irony-mode)
(add-hook 'objc-mode-hook 'irony-mode)

(add-hook 'irony-mode-hook 'irony-cdb-autosetup-compile-options)

(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(custom-safe-themes
   (quote
    ("8aebf25556399b58091e533e455dd50a6a9cba958cc4ebb0aab175863c25b9a4" "d677ef584c6dfc0697901a44b885cc18e206f05114c8a3b7fde674fce6180879" default)))
 '(package-selected-packages
   (quote
    (company-irony swift-mode swift3-mode multiple-cursors cmake-mode yaml-mode writegood-mode ace-window switch-window yasnippet-snippets yasnippet-classic-snippets web-mode solarized-theme nlinum smex rvm monokai-theme powerline paredit markdown-mode magit htmlize graphviz-dot-mode flycheck feature-mode f elpy cider autopair ac-slime))))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 )
