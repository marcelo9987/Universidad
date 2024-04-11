' mensaje sobre (about)
Dim Msg, Style, Title, Help, Ctxt, Response, MyString
Title = "Sistema Solar (© 2024)"
Msg = "Sistema Solar (© 2024)" & vbNewLine & _
      "Este programa es un simulador del Sistema Solar." & vbNewLine & _
      "Puede ver los planetas y sus órbitas." & vbNewLine & _
      "Para moverse por el espacio, use las teclas de flecha." & vbNewLine & _
      "Para acercar o alejar la vista, use las teclas c y l." & vbNewLine & _
      "Para acelerar o ralentizar el tiempo, use las teclas + y -." & vbNewLine & _
      "Para acceder al menu de cámaras, haga clic en el botón derecho del ratón."

Response = MsgBox(Msg, vbOKOnly, Title)
