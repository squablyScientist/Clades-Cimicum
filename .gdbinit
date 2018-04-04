file captcha
break receive_CAPTCHA
run 4 4 -b -d
set logging file gdb.txt
set logging on
set logging overwrite on
info frame
set logging off
continue
continue
