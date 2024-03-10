package auxiliares;
import java.util.Locale;


/**
 * Clase que contiene métodos misceláneos
 * @author Marcelo F.M.
 * @version 1.0 (global: 2.0)
 * @since 2.0 global
 */

public class Utilidades {

    public static final Locale LOCALE_SPANISH_FROM_SPAIN = new Locale("es", "ES");

    public static String getLowerCase(String string) {
        if(string == null || string.isEmpty()) {
            return string;
        }

        return string.toLowerCase(Utilidades.LOCALE_SPANISH_FROM_SPAIN);
    }

    public static boolean isEmpty(String possibleEmptyString) {
        if (possibleEmptyString == null || possibleEmptyString.isEmpty()) {
            return true;
        }
        return false;
    }

    public static Integer getIntOrNull(String possibleNumber) {
        if (isEmpty(possibleNumber)) {
            return null;
        }

        try {
            return Integer.parseInt(possibleNumber);
        }
        catch (NumberFormatException e) {
            return null;
        }
    }




}
