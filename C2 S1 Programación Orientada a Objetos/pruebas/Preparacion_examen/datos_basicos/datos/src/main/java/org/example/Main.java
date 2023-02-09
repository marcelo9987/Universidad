package org.example;

import java.util.ArrayList;

public class Main
{
    public static void main(String args[]) {
        ArrayList<Integer> nums = new ArrayList<>();
        Integer a = 10;
        Integer a2 = 10;
        Integer x = new Integer(10);
        Integer x2 = new Integer(10);
        nums.add(10);
        nums.add(10);
        nums.add(x);
        Integer y = nums.get(0);
        Integer z = nums.get(1);
        z = y;
        y++;
        y = y + 10;
        int res = y + 20;
        for (Integer val : nums)
        {
            res += val;
        }
    }
}