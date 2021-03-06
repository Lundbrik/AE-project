#include <algorithm>
#include <vector>
#include <stdio.h>
#include "nsort.h"


template <class T>
void fsort_8(std::vector<T> &data) {
    // Sort first 5 elements
    // A > B
    if (data[0] > data[1])
        std::swap(data[0], data[1]);

    // C > D
    if (data[2] > data[3])
        std::swap(data[2], data[3]);

    // A > C
    if (data[0] > data[2]) {
        std::swap(data[0], data[2]);
        std::swap(data[1], data[3]);
    }

    // E > C
    if (data[4] > data[2]) {
        // E > D
        if (data[4] > data[3]) {
            // B > D
            if (data[1] > data[3]) {
                std::swap(data[1], data[2]);
                std::swap(data[2], data[3]);
                // B > E
                if (data[3] > data[4]) {
                    std::swap(data[3], data[4]);
                }
            } else {
                // B > C
                if (data[1] > data[2]) {
                    std::swap(data[1], data[2]);
                }
            }
        } else {
            std::swap(data[3], data[4]);
            // B > E
            if (data[1] > data[3]) {
                std::swap(data[1], data[2]);
                std::swap(data[2], data[3]);
                // B > D
                if (data[3] > data[4]) {
                    std::swap(data[3], data[4]);
                }
            } else {
                // B > C
                if (data[1] > data[2]) {
                    std::swap(data[1], data[2]);
                }
            }
        }
    } else {
        std::swap(data[3], data[4]);
        std::swap(data[2], data[3]); // A B E C D
        // A > E
        if (data[0] > data[2]) {
            std::swap(data[1], data[2]);
            std::swap(data[0], data[1]); // E A B C D
            // B > C
            if (data[2] > data[3]) {
                std::swap(data[2], data[3]);
                // B > D
                if (data[3] > data[4]) {
                    std::swap(data[3], data[4]); // E A C D B
                }
            }
        } else { // A B E C D
            // B > C
            if (data[1] > data[3]) {
                std::swap(data[1], data[2]);
                std::swap(data[2], data[3]);
                if (data[3] > data[4])
                    std::swap(data[3], data[4]);
            } else {
                // B > E
                if (data[1] > data[2]) {
                    std::swap(data[1], data[2]);
                }
            }
        }
    }

    // First 5 elements sorted.

    // insert 6th element.
    if (data[2] > data[5]) {
        std::swap(data[4], data[5]);
        std::swap(data[3], data[4]);
        std::swap(data[2], data[3]);

        if (data[1] > data[2]) {
            std::swap(data[1], data[2]);

            if (data[0] > data[1])
                std::swap(data[0], data[1]);
        }
    } else {
        if (data[4] > data[5]) {
            std::swap(data[4], data[5]);
            if (data[3] > data[4])
                std::swap(data[3], data[4]);
        }
    }


    // insert 7th element.

    if (data[3] > data[6]) {
        std::swap(data[5], data[6]);
        std::swap(data[4], data[5]);
        std::swap(data[3], data[4]);

        if (data[1] > data[3]) {
            std::swap(data[2], data[3]);
            std::swap(data[1], data[2]);

            if (data[0] > data[1])
                std::swap(data[0], data[1]);
        } else {
            if (data[2] > data[3])
                std::swap(data[2], data[3]);
        }
    } else {
        if (data[5] > data[6]) {
            std::swap(data[5], data[6]);

            if (data[4] > data[5]) {
                std::swap(data[4], data[5]);
            }
        }
    }

    // Insert 8th element
    if (data[3] > data[7]) {
        std::swap(data[6], data[7]);
        std::swap(data[5], data[6]);
        std::swap(data[4], data[5]);
        std::swap(data[3], data[4]);

        if (data[1] > data[3]) {
            std::swap(data[2], data[3]);
            std::swap(data[1], data[2]);

            if (data[0] > data[1])
                std::swap(data[0], data[1]);
        } else {
            if (data[2] > data[3])
                std::swap(data[2], data[3]);
        }
    } else {
        if (data[5] > data[7]) {
            std::swap(data[6], data[7]);
            std::swap(data[5], data[6]);

            if (data[4] > data[5])
                std::swap(data[4], data[5]);
        } else {
            if (data[6] > data[7])
                std::swap(data[6], data[7]);
        }
    }

    return;
}

template <class T>
void fsort_7(std::vector<T> &data) {
    // Sort first 5 elements
    // A > B
    if (data[0] > data[1])
        std::swap(data[0], data[1]);

    // C > D
    if (data[2] > data[3])
        std::swap(data[2], data[3]);

    // A > C
    if (data[0] > data[2]) {
        std::swap(data[0], data[2]);
        std::swap(data[1], data[3]);
    }

    // E > C
    if (data[4] > data[2]) {
        // E > D
        if (data[4] > data[3]) {
            // B > D
            if (data[1] > data[3]) {
                std::swap(data[1], data[2]);
                std::swap(data[2], data[3]);
                // B > E
                if (data[3] > data[4]) {
                    std::swap(data[3], data[4]);
                }
            } else {
                // B > C
                if (data[1] > data[2]) {
                    std::swap(data[1], data[2]);
                }
            }
        } else {
            std::swap(data[3], data[4]);
            // B > E
            if (data[1] > data[3]) {
                std::swap(data[1], data[2]);
                std::swap(data[2], data[3]);
                // B > D
                if (data[3] > data[4]) {
                    std::swap(data[3], data[4]);
                }
            } else {
                // B > C
                if (data[1] > data[2]) {
                    std::swap(data[1], data[2]);
                }
            }
        }
    } else {
        std::swap(data[3], data[4]);
        std::swap(data[2], data[3]); // A B E C D
        // A > E
        if (data[0] > data[2]) {
            std::swap(data[1], data[2]);
            std::swap(data[0], data[1]); // E A B C D
            // B > C
            if (data[2] > data[3]) {
                std::swap(data[2], data[3]);
                // B > D
                if (data[3] > data[4]) {
                    std::swap(data[3], data[4]); // E A C D B
                }
            }
        } else { // A B E C D
            // B > C
            if (data[1] > data[3]) {
                std::swap(data[1], data[2]);
                std::swap(data[2], data[3]);
                if (data[3] > data[4])
                    std::swap(data[3], data[4]);
            } else {
                // B > E
                if (data[1] > data[2]) {
                    std::swap(data[1], data[2]);
                }
            }
        }
    }

    // First 5 elements sorted.

    // insert 6th element.
    if (data[2] > data[5]) {
        std::swap(data[4], data[5]);
        std::swap(data[3], data[4]);
        std::swap(data[2], data[3]);

        if (data[1] > data[2]) {
            std::swap(data[1], data[2]);

            if (data[0] > data[1])
                std::swap(data[0], data[1]);
        }
    } else {
        if (data[4] > data[5]) {
            std::swap(data[4], data[5]);
            if (data[3] > data[4])
                std::swap(data[3], data[4]);
        }
    }


    // insert 7th element.

    if (data[3] > data[6]) {
        std::swap(data[5], data[6]);
        std::swap(data[4], data[5]);
        std::swap(data[3], data[4]);

        if (data[1] > data[3]) {
            std::swap(data[2], data[3]);
            std::swap(data[1], data[2]);

            if (data[0] > data[1])
                std::swap(data[0], data[1]);
        } else {
            if (data[2] > data[3])
                std::swap(data[2], data[3]);
        }
    } else {
        if (data[5] > data[6]) {
            std::swap(data[5], data[6]);

            if (data[4] > data[5]) {
                std::swap(data[4], data[5]);
            }
        }
    }


    return;
}


template <class T>
void fsort_6(std::vector<T> &data) {
    // Sort first 5 elements
    // A > B
    if (data[0] > data[1])
        std::swap(data[0], data[1]);

    // C > D
    if (data[2] > data[3])
        std::swap(data[2], data[3]);

    // A > C
    if (data[0] > data[2]) {
        std::swap(data[0], data[2]);
        std::swap(data[1], data[3]);
    }

    // E > C
    if (data[4] > data[2]) {
        // E > D
        if (data[4] > data[3]) {
            // B > D
            if (data[1] > data[3]) {
                std::swap(data[1], data[2]);
                std::swap(data[2], data[3]);
                // B > E
                if (data[3] > data[4]) {
                    std::swap(data[3], data[4]);
                }
            } else {
                // B > C
                if (data[1] > data[2]) {
                    std::swap(data[1], data[2]);
                }
            }
        } else {
            std::swap(data[3], data[4]);
            // B > E
            if (data[1] > data[3]) {
                std::swap(data[1], data[2]);
                std::swap(data[2], data[3]);
                // B > D
                if (data[3] > data[4]) {
                    std::swap(data[3], data[4]);
                }
            } else {
                // B > C
                if (data[1] > data[2]) {
                    std::swap(data[1], data[2]);
                }
            }
        }
    } else {
        std::swap(data[3], data[4]);
        std::swap(data[2], data[3]); // A B E C D
        // A > E
        if (data[0] > data[2]) {
            std::swap(data[1], data[2]);
            std::swap(data[0], data[1]); // E A B C D
            // B > C
            if (data[2] > data[3]) {
                std::swap(data[2], data[3]);
                // B > D
                if (data[3] > data[4]) {
                    std::swap(data[3], data[4]); // E A C D B
                }
            }
        } else { // A B E C D
            // B > C
            if (data[1] > data[3]) {
                std::swap(data[1], data[2]);
                std::swap(data[2], data[3]);
                if (data[3] > data[4])
                    std::swap(data[3], data[4]);
            } else {
                // B > E
                if (data[1] > data[2]) {
                    std::swap(data[1], data[2]);
                }
            }
        }
    }

    // First 5 elements sorted.

    // insert 6th element.
    if (data[2] > data[5]) {
        std::swap(data[4], data[5]);
        std::swap(data[3], data[4]);
        std::swap(data[2], data[3]);

        if (data[1] > data[2]) {
            std::swap(data[1], data[2]);

            if (data[0] > data[1])
                std::swap(data[0], data[1]);
        }
    } else {
        if (data[4] > data[5]) {
            std::swap(data[4], data[5]);
            if (data[3] > data[4])
                std::swap(data[3], data[4]);
        }
    }

    return;
}

template <class T>
void fsort_5(std::vector<T> &data) {
    // Sort first 5 elements
    // A > B
    if (data[0] > data[1])
        std::swap(data[0], data[1]);

    // C > D
    if (data[2] > data[3])
        std::swap(data[2], data[3]);

    // A > C
    if (data[0] > data[2]) {
        std::swap(data[0], data[2]);
        std::swap(data[1], data[3]);
    }

    // E > C
    if (data[4] > data[2]) {
        // E > D
        if (data[4] > data[3]) {
            // B > D
            if (data[1] > data[3]) {
                std::swap(data[1], data[2]);
                std::swap(data[2], data[3]);
                // B > E
                if (data[3] > data[4]) {
                    std::swap(data[3], data[4]);
                }
            } else {
                // B > C
                if (data[1] > data[2]) {
                    std::swap(data[1], data[2]);
                }
            }
        } else {
            std::swap(data[3], data[4]);
            // B > E
            if (data[1] > data[3]) {
                std::swap(data[1], data[2]);
                std::swap(data[2], data[3]);
                // B > D
                if (data[3] > data[4]) {
                    std::swap(data[3], data[4]);
                }
            } else {
                // B > C
                if (data[1] > data[2]) {
                    std::swap(data[1], data[2]);
                }
            }
        }
    } else {
        std::swap(data[3], data[4]);
        std::swap(data[2], data[3]); // A B E C D
        // A > E
        if (data[0] > data[2]) {
            std::swap(data[1], data[2]);
            std::swap(data[0], data[1]); // E A B C D
            // B > C
            if (data[2] > data[3]) {
                std::swap(data[2], data[3]);
                // B > D
                if (data[3] > data[4]) {
                    std::swap(data[3], data[4]); // E A C D B
                }
            }
        } else { // A B E C D
            // B > C
            if (data[1] > data[3]) {
                std::swap(data[1], data[2]);
                std::swap(data[2], data[3]);
                if (data[3] > data[4])
                    std::swap(data[3], data[4]);
            } else {
                // B > E
                if (data[1] > data[2]) {
                    std::swap(data[1], data[2]);
                }
            }
        }
    }

    // First 5 elements sorted.

    return;
}

template <class T>
void fsort_4(std::vector<T> &data) {
    if (data[0] > data[1])
        std::swap(data[0], data[1]);

    if (data[2] > data[3])
        std::swap(data[2], data[3]);

    if (data[0] > data[2]) {
        std::swap(data[1], data[2]);
        std::swap(data[0], data[1]);

        if (data[1] > data[3]) {
            std::swap(data[2], data[3]);
            std::swap(data[1], data[2]);
        } else {
            if (data[2] > data[3])
                std::swap(data[2], data[3]);
        }
    } else {
        if (data[1] > data[2]) {
            std::swap(data[1], data[2]);

            if (data[2] > data[3])
                std::swap(data[2], data[3]);
        }
    }

    return;
}
