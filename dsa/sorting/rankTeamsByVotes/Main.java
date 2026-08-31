package dsa.sorting.rankTeamsByVotes;
import java.util.*;


public class Main {

    public String rankTeams(String[] votes) {
        int n = votes[0].length();

        int[][] ranks = new int[26][n];

        // ith team, jth rank => number of votes
        for (String vote : votes) {
            for (int i = 0; i < n; i++) {
                char team = vote.charAt(i);
                ranks[team - 'A'][i]++;
            }
        }

        // convert int to Integer to apply Arrays.sort() wala custom comparator
        Integer[] teams = new Integer[n];

        for (int i = 0; i < n; i++) {
            teams[i] = votes[0].charAt(i) - 'A';
        }

        // sort the teams using number of votes first, and then using alphabetical order
        Arrays.sort(teams, (i, j) -> {
            for (int k = 0; k < n; k++) {
                if (ranks[i][k] != ranks[j][k]) 
                    return ranks[j][k] - ranks[i][k]; // sort using number of votes (descending) at this specific rank
                
            }
            return i - j; // if votes are same, sort alphabetically
        });

        StringBuilder podium = new StringBuilder();
        for (int team: teams) {
            podium.append((char)(team + 'A'));
        }

        return podium.toString();
    }
 
    // SIR'S SOLUTION
    public String rankTeamsII(String[] votes) {
        if (votes.length == 0) return "";
        
        // we are counting how many votes did a specific character receive for all the specific cases
        Map<Character, int[]> rankByEachCharacterMap = new HashMap<>();

        for (String vote : votes) {
            for (int i = 0; i < vote.length(); i++) {
                char currMember = vote.charAt(i);
                rankByEachCharacterMap.putIfAbsent(currMember, new int[vote.length()]);
                int[] voteCount = rankByEachCharacterMap.get(currMember);
                voteCount[i]++;
            }
        }

        PriorityQueue<Map.Entry<Character, int[]>> pq = new PriorityQueue<>((e1, e2) -> {
            int[] candidateOneVotes = e1.getValue();
            int[] candidateTwoVotes = e2.getValue();
            int totalVotes = candidateOneVotes.length;

            for (int i = 0; i < totalVotes; i++) {
                if (candidateOneVotes[i] != candidateTwoVotes[i]) {
                    return Integer.compare(candidateTwoVotes[i], candidateOneVotes[i]);
                }
            }
            return Character.compare(e1.getKey(), e2.getKey());
        });

        pq.addAll(rankByEachCharacterMap.entrySet());

        StringBuilder finalRank = new StringBuilder();
        while (!pq.isEmpty()) {
            finalRank.append(pq.poll().getKey());
        }

        return finalRank.toString();
    }
}
