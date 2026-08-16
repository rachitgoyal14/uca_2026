class FindNumberRepeatedFourTimes {

    public int findNumber(int[] nums) {
        int result = 0;

        for (int k = 0; k < 32; k++) {
            int temp = (1 << k);
            int countOfOnes = 0;

            for (int num : nums) {
                if ((num & temp) != 0)
                    countOfOnes++;
            }

            if (countOfOnes%3 == 1) {
                result = result | temp;
            }
        }
        

        return result;
    }

    public static void main(String[] args) {

        FindNumberRepeatedFourTimes obj = new FindNumberRepeatedFourTimes();

        int[] nums = {2, 2, 2, 5, 5, 5, 7, 7, 7, 7};

        int result = obj.findNumber(nums);

        System.out.println("Number repeated four times: " + result);
    }
}