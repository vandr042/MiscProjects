import java.util.*;
import java.io.*;

public class Main{
	public static void main(String[] args){
		if (args.length != 1){
			System.out.println("Expecting graph file.");
			return; 
		}
		 File f = new File(args[0]);
		Scanner in = null;
		try{
			in = new Scanner(f);
		}catch (FileNotFoundException e){
			System.err.println("Could not find file.");
		}
		int verts = in.nextInt();
		int edges = in.nextInt();
		int[][] mat = new int[verts][verts];
		/* Init adjacency mat */
		for (int i = 0; i < verts; i++){
			for (int j = 0; j < verts; j++){
				if (i == j)
					mat[i][j] = 0;
				else
					mat[i][j] = 25000;	
			}
		}
		for (int i = 0; i < edges; i++){
			/* get vertex ind (vert -1) */
			int s = in.nextInt()-1;
			int v = in.nextInt()-1;
			int w = in.nextInt();
			mat[s][v] = w;
			mat[v][s] = w;
		}	
		Graph g = new Graph(mat,verts);
		Djikstra djik = new Djikstra(g,1);	 
		djik.run();
		int[] path = djik.getPath();
		int[] dist = djik.getDist();
		for (int d: dist){
			System.out.println(d);
		}
		djik.printPath(8);
	}
}
