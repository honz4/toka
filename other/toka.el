;;; toka-mode-el -- Major mode for editing Toka files

;;; Code:
(defvar toka-mode-hook nil)
(defvar toka-mode-map
  (let ((toka-mode-map (make-keymap)))
    (define-key toka-mode-map "\C-j" 'newline-and-indent)
    toka-mode-map)
  "Keymap for toka major mode")

(add-to-list 'auto-mode-alist '("\\.toka\\'" . toka-mode))

(defconst toka-font-lock-keywords-1
  (list
    '("\\<\\(\\iterate\\|\\+iterate\\|\\ifTrueFalse\\|\\ifTrue\\|\\ifFalse\\|\\whileTrue\\|\\whileFalse\\|\\[\\|\\]\\|\\is\\|\\is-macro\\|\\is-data\\|\\is-array\\|\\variable\\)\\>" . font-lock-builtin-face)
    '("\\<\\(\\heap\\|\\escape-sequences\\|\\last\\|\\base\\|\\compiler\\|\\parser\\)\\>" . font-lock-variable-name-face)
    '("\\<\\(\\TRUE\\|\\FALSE\\|\\\"R\"\\|\\\"W\"\\|\\\"A\"\\|\\\"R+\"\\|\\\"W+\"\\|\\\"A+\"\\|\\START\\|\\END\\|\\CURRENT\\|\\cell-size\\|\\char-size\\)\\>" . font-lock-constant-face)
    '("\\<\\(\\file.open\\|\\file.close\\|\\file.read\\|\\file.write\\|\\file.size\\|\\file.slurp\\)\\>" . font-lock-keyword-face)
    '("\\<\\(\\dup\\|\\drop\\|\\swap\\|\\over\\|\\nip\\|\\tuck\\|\\rot\\|\\-rot\\|\\depth\\|\\reset\\)\\>" . font-lock-function-name-face)
  )
)


(defvar toka-font-lock-keywords toka-font-lock-keywords-1
  "Default highlighting expressions for toka mode.")

(defvar toka-mode-syntax-table
  (let ((toka-mode-syntax-table (make-syntax-table)))
	(modify-syntax-entry ?! "w" toka-mode-syntax-table)
	(modify-syntax-entry ?@ "w" toka-mode-syntax-table)
	(modify-syntax-entry ?# "w" toka-mode-syntax-table)
	(modify-syntax-entry ?/ "w" toka-mode-syntax-table)
	(modify-syntax-entry ?* "w" toka-mode-syntax-table)
	(modify-syntax-entry ?[ "w" toka-mode-syntax-table)
	(modify-syntax-entry ?] "w" toka-mode-syntax-table)
	(modify-syntax-entry ?_ "w" toka-mode-syntax-table)
	(modify-syntax-entry ?+ "w" toka-mode-syntax-table)
	(modify-syntax-entry ?- "w" toka-mode-syntax-table)
	(modify-syntax-entry ?/ ". 124b" toka-mode-syntax-table)
	(modify-syntax-entry ?* ". 23" toka-mode-syntax-table)
	(modify-syntax-entry ?\n "> b" toka-mode-syntax-table)
	toka-mode-syntax-table)
)
  
(defun toka-mode ()
  (interactive)
  (kill-all-local-variables)
  (use-local-map toka-mode-map)
  (set-syntax-table toka-mode-syntax-table)
  ;; Set up font-lock
  (set (make-local-variable 'font-lock-defaults) '(toka-font-lock-keywords))
  ;; Register our indentation function
  (set (make-local-variable 'indent-line-function) 'toka-indent-line)  
  (setq major-mode 'toka-mode)
  (setq mode-name "toka")
  (run-hooks 'toka-mode-hook))

(provide 'toka-mode)

;;; toka-mode.el ends here
