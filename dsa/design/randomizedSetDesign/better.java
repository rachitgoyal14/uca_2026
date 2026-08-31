package dsa.design.randomizedSetDesign;
import java.util.*;

class RandomizedSet {

    private HashMap<Integer, Integer> map;
            // value, index;
    private ArrayList<Integer> arr;

    RandomizedSet(){
        map = new HashMap<>();
        arr = new ArrayList<>();
    }

    boolean insert(int val) {
        boolean valuePresentInitially = false;

        if (!map.containsKey(val)) {
            valuePresentInitially = true;

            arr.add(val);
            map.put(val, arr.size() - 1);  
        }

        return valuePresentInitially;
    }

    boolean remove(int val){
        boolean valuePresentInitially = false;
        // fancy removal
        if (map.containsKey(val)) {
            valuePresentInitially = true;

            int index = map.get(val);       
            int lastVal = arr.get(arr.size() - 1);

            arr.set(index, lastVal);        
            map.put(lastVal, index);        

            arr.remove(arr.size() - 1);    
            map.remove(val);
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


public class better {
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