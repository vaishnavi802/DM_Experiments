#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

struct Point {
    double x, y;
};

struct Cluster {
    Point center;
    std::vector<Point> points;
};

double calculateDistance(const Point& p1, const Point& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

void initializeRandomPoints(std::vector<Point>& data, int numPoints) {
    // Initialize random number generator
    std::srand(static_cast<unsigned>(std::time(0)));

    // Generate random data points
    for (int i = 0; i < numPoints; ++i) {
        Point p;
        p.x = static_cast<double>(std::rand()) / RAND_MAX * 10.0;  // Random x-coordinate between 0 and 10
        p.y = static_cast<double>(std::rand()) / RAND_MAX * 10.0;  // Random y-coordinate between 0 and 10
        data.push_back(p);
    }
}

void kMeansClustering(std::vector<Point>& data, std::vector<Cluster>& clusters, int maxIterations) {
    for (int iteration = 0; iteration < maxIterations; ++iteration) {
        // Assign points to clusters
        for (Point& p : data) {
            double minDistance = std::numeric_limits<double>::max();
            int clusterIndex = 0;

            for (size_t i = 0; i < clusters.size(); ++i) {
                double distance = calculateDistance(p, clusters[i].center);
                if (distance < minDistance) {
                    minDistance = distance;
                    clusterIndex = i;
                }
            }

            clusters[clusterIndex].points.push_back(p);
        }

        // Update cluster centers
        for (Cluster& cluster : clusters) {
            if (!cluster.points.empty()) {
                double sumX = 0.0, sumY = 0.0;
                for (const Point& p : cluster.points) {
                    sumX += p.x;
                    sumY += p.y;
                }
                cluster.center.x = sumX / cluster.points.size();
                cluster.center.y = sumY / cluster.points.size();
            }
        }

        // Clear points in clusters for the next iteration
        for (Cluster& cluster : clusters) {
            cluster.points.clear();
        }
    }
}

int main() {
    std::vector<Point> data;
    initializeRandomPoints(data, 50);  // Generate 50 random data points

    std::vector<Cluster> clusters{
        {{2.0, 2.0}, {}},  // Initial center for cluster 1
        {{8.0, 8.0}, {}}   // Initial center for cluster 2
    };

    kMeansClustering(data, clusters, 100);

    // Display clusters and their points
    for (size_t i = 0; i < clusters.size(); ++i) {
        std::cout << "Cluster " << i + 1 << " Center: (" << clusters[i].center.x << ", " << clusters[i].center.y << ")\n";
        std::cout << "Points in Cluster " << i + 1 << ":\n";
        for (const Point& p : clusters[i].points) {
            std::cout << "(" << p.x << ", " << p.y << ") ";
        }
        std::cout << "\n\n";
    }

    return 0;
}
