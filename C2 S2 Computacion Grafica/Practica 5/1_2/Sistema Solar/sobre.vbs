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
      "Para moverse por el espacio, use las teclas de flecha." & vbNewLine & _
      "Para acercar o alejar la vista, use las teclas c y l." & vbNewLine & _
      "Para acelerar o ralentizar el tiempo, use las teclas + y -." & vbNewLine & _
      "Para acceder al menu de cámaras, haga clic en el botón derecho del ratón."

Response = CustomMsgBox(Msg, vbOKOnly, Title)

WScript.Echo "Response: " & Response
