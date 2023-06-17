#pragma once

#include <vector>
#include "../utils/point_2D.hpp"
#include "../utils/vp.hpp"
#include "../utils/maths.hpp"
#include "../utils/constants.hpp"

class sampler{
public:
    sampler(int samples = 1, int sets = 50);
    sampler(const sampler& samp);
    sampler& operator=(const sampler& rhs);
    virtual sampler* clone() const = 0;

    virtual ~sampler();

    int get_num_samples();
    void set_num_samples(int samples);

    int get_num_sets();
    void set_num_sets(int sets);

    point_2D sample_unit_square();

    void map_samples_to_unit_disk();
    void map_samples_to_hemisphere(const float e);
    point_2D sample_unit_disk();
    vp sample_hemisphere();

protected:
    int num_samples;                    // the number of sample points in a pattern
    int num_sets;                       // the number of sample sets (patterns) stored
    unsigned long count;                // the current number of sample points used
    int jump;                           // random index jump

    std::vector<point_2D> samples;      // sample points on a unit square
    std::vector<int> shuffled_indices;  // shuffled samples array indices
    std::vector<point_2D> disk_samples;
    std::vector<vp> hemisphere_samples;

    virtual void generate_samples() = 0;
    void shuffle_x_coordinates();
    void shuffle_y_coordinates();
};
