package auxiliares;

public class Criptografia {

    /**
     * Cifra un texto usando el cifrado de César
     *
     * @param input texto a cifrar
     * @return texto cifrado
     */
    public static String cifradoCaesar(String input) {
        int factor_desplazamiento = 152658;
        StringBuilder result = new StringBuilder();
        for (char character : input.toCharArray()) {
            if (Character.isLetter(character)) {
                char base = Character.isLowerCase(character) ? 'a' : 'A';
                result.append((char) (((character + factor_desplazamiento - base) % 26) + base));
            }
            else {
                result.append(character);
            }
        }
        return result.toString();
    }

    /**
     * Descifra un texto usando el cifrado de César
     *
     * @param input texto a descifrar
     * @return texto descifrado
     */
    public static String descifradoCaesar(String input) {
        int factor_desplazamiento = 152658 % 26;
        StringBuilder result = new StringBuilder();
        for (char character : input.toCharArray()) {
            if (Character.isLetter(character)) {
                char base = Character.isLowerCase(character) ? 'a' : 'A';
                result.append((char) (((character - factor_desplazamiento - base + 26) % 26) + base));
            }
            else {
                result.append(character);
            }
        }
        return result.toString();
    }
}
