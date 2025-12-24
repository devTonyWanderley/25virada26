;;;	--HEAD--
(regapp "PONTO")

;;;	--ROTINAS--
;;;		--I/O--
;;;			--ARQUIVO--
(defun top:get_na(msg dir ex f) (getfiled msg dir ex f))

(defun top:norma_tx(arg / c r)
  (setq r "")
  (while (/= (setq c (substr arg 1 1) arg (substr arg 2) c c) "")
    (if (or (wcmatch c "@") (wcmatch c "#"))
      (setq r (strcat r c))
      )
    )
  r
  )

(defun top:get_linha(arg / r)
  (setq r (list (+ (atof (substr arg 38 4)) (/ (atof (substr arg 43 3)) 1000.0)))
	r (cons (+ (atof (substr arg 27 7)) (/ (atof (substr arg 35 3)) 1000.0)) r)
	r (cons (+ (atof (substr arg 17 7)) (/ (atof (substr arg 24 3)) 1000.0)) r)
	r (cons (top:norma_tx (substr arg 9 8)) r)
	r (cons (top:norma_tx (substr arg 1 8)) r)
	)
  )

(defun top:get_arq(/ na pa ln lt)
  (if (setq na (top:get_na "msg" "C:/2025/Soft/InstLocal/" "txt" 0))
    (if (setq pa (open na "r"))
      (progn
	(while (setq ln (read-line pa))
	  (setq lt (cons (top:get_linha ln) lt))
	  )
	(setq pa (close pa))
	)
      )
    )
  (reverse lt)
  )

;;;			--DESENHO--

;;;		--DESENHAR--
(defun top:faz-point(arg la 3d)
  (entmake (list (cons 0 "POINT") (cons 8 la)
		 (list 10 (nth 2 arg) (nth 3 arg) (if 3d (nth 4 arg) 0.0))
		 (list -3
		       (list "PONTO"
			     (cons 1000 (car arg))
			     (cons 1000 (cadr arg))
			     (cons 1010 (cddr arg))
			     )
		       )
		 )
	   )
  )

;;;	--CHAMADAS--
(defun c:teste_lsp(/ lt i)
  (alert "Lançar pontos")
  (if (setq lt (top:get_arq))
    (while (nth (setq i (if i (1+ i) 0)) lt)
      (top:faz-point (nth i lt) "_Pontos" nil)
      )
    (alert "algo errado.")
    )
  )