cat /etc/passwd > passwd_copia 

cat /etc/passwd >> passwd_copia 

wc passwd_copia 

wc /etc/passwd 

sort passwd_copia | uniq > passwd_original 

wc passwd_original 

diff <(sort /etc/passwd) passwd_original 

 

cat /etc/passwd > passwd_copia 
 
cat /etc/passwd >> passwd_copia 
 
wc passwd_copia 
 
wc /etc/passwd 
 
sort passwd_copia | uniq > passwd_original 
 
wc passwd_original 
 
diff <(sort /etc/passwd) passwd_original