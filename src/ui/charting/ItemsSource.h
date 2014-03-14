#pragma once;

#include "..\..\Vec2.h"

#include <algorithm>
#include <numeric>
#include <vector>

namespace zlx
{
    namespace ui
    {
        namespace charting
        {
            template<class Tx, class Ty>
            struct DataItem
            {
                DataItem(Tx x_, Ty y_)
                    : x(x_), y(y_) { }

                Tx x;
                Ty y;
            };

            struct PlotStats
            {
                PlotStats()
                {
                    min_x = std::numeric_limits<double>::max();
                    max_x = std::numeric_limits<double>::min();

                    min_y = std::numeric_limits<double>::max();
                    max_y = std::numeric_limits<double>::min();
                }

                double min_x;
                double max_x;
                double min_y;
                double max_y;

                double delta_x() { return max_x - min_x; }
                double delta_y() { return max_y - min_y; }
            };

            template<class Tx, class Ty>
            PlotStats calculate_stats(std::vector<DataItem<Tx, Ty>> data)
            {
                PlotStats stats;

                for (const auto& x : data)
                {
                    stats.min_x = std::min(stats.min_x, (double)x.x);
                    stats.min_y = std::min(stats.min_y, (double)x.y);

                    stats.max_x = std::max(stats.max_x, (double)x.x);
                    stats.max_y = std::max(stats.max_y, (double)x.y);
                }

                return stats;
            }

            class ItemsSourceBase
            {
            public:
                virtual PlotStats calculate() = 0;
                virtual const std::vector<Point2> get_data_points() const = 0;
                virtual bool is_ready() const = 0;
                virtual ~ItemsSourceBase() { }
            };

            template<class Tx, class Ty>
            class ItemsSource : public ItemsSourceBase
            {
            public:

                typedef typename DataItem<Tx, Ty> Item;

                typedef typename std::vector<Item> Vector;
           
                ItemsSource() : ready(false) { }

                //Client Data, Input
                Vector& get_data_source()
                {
                    return data_source;
                }  

                bool is_ready() const override { return ready; }

                //Output
                const std::vector<Point2> get_data_points() const override
                {
                    return data_points;
                }

                PlotStats calculate() override
                {
                    data_points.clear();
                    auto stats = calculate_stats(data_source);

                    double dx = stats.delta_x();
                    double dy = stats.delta_y();

                    for (const auto& item : data_source)
                    {
                        double x = dx != 0.0 ? (item.x - stats.min_x) / dx : dx;
                        double y = dy != 0.0 ? (item.y - stats.min_y) / dy : dy;

                        Point2 data_point((float)x, (float)y);

                        data_points.push_back(data_point);
                    }

                    ready = true;

                    return stats;
                }

            private:
                Vector data_source;
                std::vector<Point2> data_points;

                bool ready;
            };

            typedef ItemsSource<float, float> ItemsSource_f;
        }
    }
}