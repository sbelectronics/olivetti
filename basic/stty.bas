10 EXEC "RS232"
20 EXEC "sc com:,19200,none,0,8,half,off,2048"
30 EXEC "ci 0,o,0"
40 EXEC "+scom:, +dcom:"
50 PRINT "Serial Console Enabled"
60 SYSTEM
70 REM Note: use "-scom,-dcom" prior to psave otherwise
80 REM VQ and friends will be broken until you do the CI
90 REM to open the port

