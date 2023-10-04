libmat ← &i "modulos.ua"
mmul ← use "mmul" libmat

# Inicio el ej. 3
A ← [[1][2]]
B ← [5 3]
AB ← mmul A B
Ea ← AB
# &pf "AB:"
AB

C ← [[2 1 1][1 1 0]]
CT ← ⍉ C
CTC ← mmul CT C
Eb ← CTC
# &pf "CTC:"
CTC

D ← [[1 ¯2][1 ¯1][0 ¯1]]
DC ← mmul D C
Ec ← DC
# &pf "DC:"
DC

Ed ← [[1 ¯1 1][¯1 0 1][2 ¯1 1]]
Ed

Todos ← {Ea Eb Ec Ed}
# Todos
# ⊏ 1 Todos # selecciona el primer elemento del array todos

# MatAct ← ⍉ ⊏ 0 Todos

TodosTrans ← ∵⍉Todos

sumaTodos ← + TodosTrans Todos
sumaTodos

restaTodos ← - TodosTrans Todos
restaTodos
