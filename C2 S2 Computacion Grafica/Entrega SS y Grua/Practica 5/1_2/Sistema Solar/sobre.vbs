' mensaje sobre (about)

' una funcion con el cuadro de texto que devuelva 1 si se pulsa aceptar
' y 2 si se pulsa cancelar
Function CustomMsgBox(Msg, Style, Title)
    CustomMsgBox = MsgBox(Msg, Style, Title)
    Exit Function
End Function

Dim Msg, Style, Title, Help, Ctxt, Response, MyString
Title = "Sistema Solar (© 2024)"
Msg = "Sistema Solar (© 2024)" & vbNewLine & _
      "Este programa es un simulador del Sistema Solar." & vbNewLine & _
      "Puede ver los planetas y sus órbitas." & vbNewLine & _
      "- Teclas de flechas: para moverse por el espacio" & vbNewLine & _
      "- Teclas c y l: a(c)ercar o a(l)ejar la vista" & vbNewLine & _
      "- Teclas + y -: acelerar o ralentizar el tiempo" & vbNewLine & _
      "- Tecla r y F10: resetear simulación" & vbNewLine & _
      "- Tecla o: encender / apagar las órbitas" & vbNewLine & _
      "- Tecla s: encender / apagar el sol" & vbNewLine & _
      "- Tecla m: encender / apagar monitores" & vbNewLine & _
      "- Tecla e: algún Easter Egg" & vbNewLine & _
      "- Tecla h: mostrar esta ayuda" & vbNewLine & _
      "- Tecla Escape: salir el programa" & vbNewLine & _
      "- Clic en el botón derecho del ratón: acceder al menu de cámaras"

'_Msg = "Sistema Solar (© 2024)" & vbNewLine & _

Response = CustomMsgBox(Msg, vbOKOnly, Title)

WScript.Echo "Response: " & Response
