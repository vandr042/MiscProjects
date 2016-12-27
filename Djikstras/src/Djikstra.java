import java.util.*;
public class Djikstra{
	private int source;
	private int[][] adj;
	private int[] dist;
	private int[] path;
	private int verts;
	public Djikstra(Graph g, int source){
		this.adj = g.getAdjMat();
		this.verts = g.getNumVerts();
		this.source = source;
		this.dist = new int[this.verts];
		this.path = new int[this.verts];
	}

	public void run(){
		int srcInd = source-1;
		AbstractQueue<vdTup> pq = new PriorityQueue<>();

		dist[srcInd] = 0;		
		vdTup src = new vdTup(srcInd, dist[srcInd]);
		pq.add(src);

		/* Add vertices to Q */
		for (int i = 0; i < this.verts; i++){
			if (i == srcInd)
				continue;
			
			dist[i] = 25000;
		}


		/* Compute shortest paths */
		while (pq.size() != 0){
			vdTup u = pq.poll();
			for (int i = 0; i < this.verts; i++){
				int alt = u.dist + adj[u.vert][i];
				if (alt  < dist[i]){
					dist[i] = alt;
					/* remove if already in q */
					vdTup v = new vdTup(i, dist[i]);	
					boolean r = pq.remove(v);
					pq.add(v);
					path[i] = u.vert+1; 
				}
			}
		}			
	}
	public int[] getDist(){
		return this.dist;
	}

	public int[] getPath(){
		return this.path;
	}

	public void printPath(int dest){
		if (dest == source){
			System.out.print(dest + " ");
			return;
		}
		int destInd = dest-1;
		printPath(path[destInd]);
		System.out.print(dest+ " ");
	}
	private class vdTup implements Comparator<vdTup>,Comparable<vdTup>{
		int vert;
		int dist;
		public vdTup(int vert, int dist){
			this.vert = vert;
			this.dist = dist;
		}
		public int compareTo(vdTup o){
			Integer i1 = new Integer(this.dist);
			Integer i2 = new Integer(o.dist);
			return i1.compareTo(i2);	
		} 
		public int compare(vdTup o1, vdTup o2){
			return o1.compareTo(o2);
		} 
		@Override
		public boolean equals(Object o){
			vdTup v = (vdTup) o;
			if (this.vert == v.vert)
				return true;
			else
				return false;
		}
	}
}
