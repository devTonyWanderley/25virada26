;;;	--HEAD--
(setq #param-leitura '(("PONTO" "Arquivo de pontos" "C:/2025/Soft/InstLocal/" "txt")
		       ("ARESTA" "Arquivo de arestas" "C:/2025/Soft/InstLocal/" "txt")
		       ("FACE" "Arquivo de faces" "C:/2025/Soft/InstLocal/" "txt")
		       )
      #param-desenho '(("PONTO" "_Pontos" 0.1)
		       ("ARESTA" "_Arestas")
		       ("FACE" "_Faces")
		       )
      )

;;;	--ROTINAS--
;;;		--INICIALIZAÇÃO--
(defun top:inicia(/ i)
  (while (nth (setq i (if i (1+ i) 0)) #param-leitura)
    (regapp (car (nth i #param-leitura)))
    )
  (princ "TOP carregado com sucesso")
  )

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

(defun top:ler-ln-ponto(arg / r)
  (setq r (list (+ (atof (substr arg 38 4)) (/ (atof (substr arg 43 3)) 1000.0)))
	r (cons (+ (atof (substr arg 27 7)) (/ (atof (substr arg 35 3)) 1000.0)) r)
	r (cons (+ (atof (substr arg 17 7)) (/ (atof (substr arg 24 3)) 1000.0)) r)
	r (cons (top:norma_tx (substr arg 9 8)) r)
	r (cons (top:norma_tx (substr arg 1 8)) r)
	)
  )

(defun top:ler-arquivo(chave / na pa ln lt)
  (if (setq na (top:get_na
		 (cadr (assoc chave #param-leitura))
		 (caddr (assoc chave #param-leitura))
		 (nth 3 (assoc chave #param-leitura))
		 0
		 )
	    )
    (if (setq pa (open na "r"))
      (progn
	(while (setq ln (read-line pa))
	  (setq lt (cons ln lt))
	  )
	(setq pa (close pa))
	)
      (princ "erro no arquivo\n")
      )
    (princ "erro no nome do arquivo\n")
    )
  (if lt
    (reverse lt)
    (princ)
    )
  )

;;;			--DESENHO--
(defun top:ler-xdata(en)
  (if (setq en (assoc -3
		      (if (listp en)
			(if (= (type (car en)) 'ename)
			  (entget (car en) (mapcar 'car #param-leitura))
			  en
			  )
			(entget en (mapcar 'car #param-leitura))
			)
		      )
	    )
    (mapcar 'cdr (cdadr en))
    )
  )

(defun top:tipo-de-xdata(en)
  (if (setq en (assoc -3
		      (if (listp en)
			(if (= (type (car en)) 'ename)
			  (entget (car en) (mapcar 'car #param-leitura))
			  en
			  )
			(entget en (mapcar 'car #param-leitura))
			)
		      )
	    )
    (caadr en)
    )
  )

(defun top:varre-xdata(tipo / en len)
  (while (setq en (if en (entnext en) (entnext)))
    (if (= (top:tipo-de-xdata en) tipo)
      (setq len (cons (top:ler-xdata en) len))
      )
    )
  (reverse len)
  )

(defun top:select-pra-aresta(/ n en lt)
  (while (< (setq n (if n n 0)) 6)
    (if (setq en (entsel "\nSelecione"))
      (if (= (top:tipo-de-xdata en) "PONTO")
	(setq n (+ n 2)
	      lt (cons (top:ler-xdata en) lt)
	      )
	(if (= (top:tipo-de-xdata en) "ARESTA")
	  (setq n (+ n 2)
		lt (cons (top:ler-xdata en) lt)
		)
	  )
	)
      (setq n (+ n 7))
      )
    )
  lt
  )

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

(defun top:mostra-cotas-e-atrs(/ lt i x y h tx)
  (if (setq lt (top:varre-xdata "PONTO"))
    (while (nth (setq i (if i (1+ i) 0)) lt)
      (progn
	(setq x (car (last (nth i lt)))
	      y (- (cadr (last (nth i lt))) (* (caddr (assoc "PONTO" #param-desenho)) 2.5))
	      h (* 1.5 (caddr (assoc "PONTO" #param-desenho)))
	      tx (rtos (last (last (nth i lt))) 2 3)
	      )
	(entmake (list (cons 0 "TEXT") (cons 8 "_Cotas") (list 10 x y 0.0) (cons 40 h) (cons 1 tx)))
	(setq y (+ y (* (caddr (assoc "PONTO" #param-desenho)) 3.5))
	      tx (cadr (nth i lt))
	      )
	(entmake (list (cons 0 "TEXT") (cons 8 "_Atributos") (list 10 x y 0.0) (cons 40 h) (cons 1 tx)))
	)
      )
    )
  (princ)
  )

;;;	--INTERMEDIÁRIOS DE CHAMADAS--
(defun top:lança-pontos(3d / lt i)
  (setvar "pdmode" 35)
  (setvar "pdsize" (caddr (assoc "PONTO" #param-desenho)))
  (if (setq lt (top:ler-arquivo "PONTO"))
    (while (nth (setq i (if i (1+ i) 0)) lt)
      (top:faz-point (top:ler-ln-ponto (nth i lt)) (cadr (assoc "PONTO" #param-desenho)) 3d)
      )
    (princ "erro ao lançar pontos")
    )
  (princ)
  )

;;;	--CHAMADAS--
(defun c:teste_lsp(/ lt i)
  (alert "Lançar pontos")
  )

(defun c:lança-pontos-2d()(top:lança-pontos nil))
(defun c:lança-pontos-3d()(top:lança-pontos 't))
(defun c:cotas-e-atributos()(top:mostra-cotas-e-atrs))
(top:inicia)