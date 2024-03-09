package auxiliares;

import javax.swing.text.NumberFormatter;
import java.text.NumberFormat;

public class IntegerFormatter extends NumberFormatter {

    public static NumberFormatter getNaturalNumberFieldFormatter() {
        return getNumberFieldFormatter(0, Integer.MAX_VALUE);
    }

    public static NumberFormatter getNumberFieldFormatter(int min, int max) {
        // NumberFormat integerFieldFormat = NumberFormat.getInstance();

        NumberFormat integerFieldFormat = NumberFormat.getIntegerInstance();
        integerFieldFormat.setGroupingUsed(false);

        // --

        NumberFormatter integerFieldFormatter = new IntegerFormatter(integerFieldFormat);
        integerFieldFormatter.setValueClass(Integer.class);
        integerFieldFormatter.setMinimum(min);
        integerFieldFormatter.setMaximum(max);
        integerFieldFormatter.setAllowsInvalid(false);
        // If you want the value to be committed on each keystroke instead of focus lost
        integerFieldFormatter.setCommitsOnValidEdit(true);

        // --

        return integerFieldFormatter;
    }

    public IntegerFormatter(NumberFormat format) {
        super(format);
    }

    @Override
    public Object stringToValue(String text) throws java.text.ParseException {
        if (text == null || text.isEmpty()) {
            return null;
        }
        return super.stringToValue(text);
    }

}
