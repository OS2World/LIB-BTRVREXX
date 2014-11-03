/* Btrieve */
call RxFuncAdd 'BTRV', 'BTRVREXX', 'BTRV'
datalen = 5
posblock = left("", 128)
databuffer = left("", 256)
keybuffer = left("", 255)
rc = BTRV(26, 'posblock', 'databuffer', 'datalen', 'keybuffer', 0)
say 'RC 'length(rc) rc
say 'DATALEN 'datalen length(databuffer)
say 'DATA 'c2d(substr(databuffer, 1, 2)) c2d(substr(databuffer, 3, 2)) substr(databuffer, 5, 1)
say 'KEY 'left(keybuffer, 5) length(keybuffer)
call RxFuncDrop 'BTRV'
