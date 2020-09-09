from datetime import datetime
from time import sleep


class TouchedIterator:
    def __init__(self, touches, depths, rgbs, delay=False):
        self.result = []
        self.index = 0
        self.total_delay = 0

        def find_closest(target_time, times_list):
            return min(times_list, key=lambda t: abs(target_time - t))

        rgb_keys = iter(sorted(rgbs.keys()))
        next_rgb = closest_rgb = next(rgb_keys)

        depths_keys = iter(sorted(depths.keys()))
        next_depths = closest_depths = next(depths_keys)

        for observation_ts, observations in sorted(touches.items()):
            for observation in observations:
                if closest_rgb == next_rgb:
                    try:
                        next_rgb = next(rgb_keys)
                    except StopIteration:
                        pass
                closest_rgb = find_closest(
                    observation_ts, [closest_rgb, next_rgb],
                )

                if closest_depths == next_depths:
                    try:
                        next_depths = next(depths_keys)
                    except StopIteration:
                        pass
                new_closest = find_closest(
                    observation_ts, [closest_depths, next_depths],
                )
                time_delta_in_seconds = (
                    new_closest - closest_depths
                ).total_seconds()
                closest_depths = new_closest

                if delay and time_delta_in_seconds > 0:
                    self.total_delay += time_delta_in_seconds
                    sleep(time_delta_in_seconds)
                self.result.append(
                    (
                        observation_ts,
                        observation,
                        rgbs[closest_rgb],
                        depths[new_closest],
                    ),
                )

    def __iter__(self):
        return self

    def __next__(self):
        if self.index != len(self.result):
            self.index += 1
            return self.result[self.index - 1]
        raise StopIteration()

    def get_total_delay(self):
        return self.total_delay


class TestInput:
    def test1(self):
        def fromiso(time):
            return datetime.fromisoformat(time)

        touches_ = {
            fromiso('2020-09-09 10:26:39.511879'): [12, 13],
            fromiso('2020-09-09 10:26:38.511879'): [10, 11],
        }
        rgbs_ = {
            fromiso('2020-09-09 10:26:38.411879'): 1,
            fromiso('2020-09-09 10:26:39.411879'): 2,
        }
        depths_ = {
            fromiso('2020-09-09 10:26:38.611879'): 'frame-000000.png',
            fromiso('2020-09-09 10:26:39.611879'): 'frame-000001.png',
        }
        expected_list_ = [
            (
                datetime(2020, 9, 9, 10, 26, 38, 511879),
                10,
                1,
                'frame-000000.png',
            ),
            (
                datetime(2020, 9, 9, 10, 26, 38, 511879),
                11,
                1,
                'frame-000000.png',
            ),
            (
                datetime(2020, 9, 9, 10, 26, 39, 511879),
                12,
                2,
                'frame-000001.png',
            ),
            (
                datetime(2020, 9, 9, 10, 26, 39, 511879),
                13,
                2,
                'frame-000001.png',
            ),
        ]
        expected_delay_ = 1
        return touches_, rgbs_, depths_, expected_list_, expected_delay_


touches, rgbs, depths, expected_list, expected_delay = TestInput().test1()

touched = TouchedIterator(touches, depths, rgbs)
if expected_list == list(touched):
    print('passed')
if touched.get_total_delay() == 0:
    print('passed')

touched = TouchedIterator(touches, depths, rgbs, delay=True)
if expected_list == list(touched):
    print('passed')
if touched.get_total_delay() == expected_delay:
    print('passed')
