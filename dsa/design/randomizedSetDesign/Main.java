package dsa.design.randomizedSetDesign;
import java.util.*;

class RandomizedSet {

    private HashSet<Integer> set;
    private ArrayList<Integer> arr;

    RandomizedSet(){
        set = new HashSet<>();
        arr = new ArrayList<>();
    }

    boolean insert(int val) {
       boolean valuePresentInitially = false;
        if (!set.contains(val)) {
            valuePresentInitially = true;
            set.add(val);
            arr.add(val);
        }
        return valuePresentInitially;
    }

    boolean remove(int val){
        boolean valuePresentInitially = false;
        if (set.contains(val)) {
            valuePresentInitially = true;
            set.remove(val);
            arr.remove(arr.indexOf(val));
        }
        return valuePresentInitially;
    }

    int getRandom() {
        int n = arr.size();
        Random random = new Random();
        int randomIndex = random.nextInt(n); 
        return arr.get(randomIndex);
    }
}



public class Main {
    public static void main(String[] args) {
        RandomizedSet r1 = new RandomizedSet();
        System.out.println(r1.insert(1));
        System.out.println(r1.remove(2));
        System.out.println(r1.insert(2));
        System.out.println(r1.getRandom());
        System.out.println(r1.remove(1));
        System.out.println(r1.getRandom());
    }
}
