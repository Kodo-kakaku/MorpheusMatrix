#pragma once

#include <map>
#include <iterator>

namespace mtx
{
    namespace {
        template<typename T, typename InternalIterator>
        class MatrixIterator
        {
            InternalIterator it;

        public:

            MatrixIterator(InternalIterator _it)
            {
                it = _it;
            }

            auto operator->()
            {
                return &(std::tuple_cat(it->first, std::make_tuple(it->second)));
            }

            auto operator*()
            {
                return std::tuple_cat(it->first, std::make_tuple(it->second));
            }

            MatrixIterator& operator++()
            {
                ++it;
                return *this;
            }

            bool operator!=(const MatrixIterator& right)
            {
                return it != right.it;
            }

            bool operator==(const MatrixIterator& right)
            {
                return it == right.it;
            }
        };

        template<typename Array, std::size_t... I>
        auto a2t_impl(const Array& a, std::index_sequence<I...>)
        {
            return std::make_tuple(a[I]...);
        }

        template<typename T, int size>
        struct make_one_type_tuple
        {
            T tmp_arr[size];
            using type = decltype(a2t_impl(tmp_arr, std::make_index_sequence<size>{}));
        };

        template<typename T, int size>
        using make_one_type_tuple_t = typename make_one_type_tuple<T, size>::type;
    }

    template<typename T, int DEFAULT_VALUE, int DIM = 2>
    class Matrix
    {
        using SyzeType = size_t;
        using KeyType = make_one_type_tuple_t<SyzeType, DIM>;
        using ContanerType = std::map<KeyType, T>;

        using ContanerIteratorType = typename ContanerType::iterator;

        template<int pos, typename IndexesType>
        struct MatrixE
        {
            MatrixE(Matrix& _matrix, IndexesType _indexes) :
                    indexes(_indexes), matrix(_matrix) {}

            auto operator[](int index) {
                return MatrixE<pos - 1, decltype(std::tuple_cat(indexes, std::make_tuple(index)))>
                        (matrix, std::tuple_cat(indexes, std::make_tuple(index)));
            }
        private:
            const IndexesType indexes;
            Matrix& matrix;
        };

        template< typename IndexesType>
        struct MatrixE<1, IndexesType>
        {
            MatrixE(Matrix& _matrix, IndexesType _indexes) :
                    indexes(_indexes), matrix(_matrix) { }

            operator T() const {
                auto it = matrix.cells.find(indexes);
                if (it != matrix.cells.end())
                    return it->second;
                return DEFAULT_VALUE;
            }

            MatrixE& operator= (T v) & {
                applyValue(v);
                return *this;
            }

            MatrixE& operator= (const MatrixE& acc) & {
                return *this = (T)acc;
            }

            MatrixE&& operator= (T v) && {
                applyValue(v);
                return std::move(*this);
            }

            MatrixE&& operator= (const MatrixE& acc) && {
                return std::move(*this) = (T)acc;
            }

            friend bool operator== (const MatrixE& lhs, const MatrixE& rhs) {
                return (T)lhs == (T)rhs;
            }

        private:
            IndexesType indexes;
            Matrix& matrix;

            void applyValue(T v) {
                if (v == DEFAULT_VALUE) {
                    auto it = matrix.cells.find(indexes);
                    if (it != matrix.cells.end())
                        matrix.cells.erase(indexes);
                }
                else {
                    matrix.cells.insert_or_assign(indexes, v);
                }
            }
        };

    public:
        Matrix();
        ~Matrix();

        size_t size() {
            return cells.size();
        }

        auto begin() {
            return MatrixIterator<T, ContanerIteratorType>(cells.begin());
        }
        auto end() {
            return MatrixIterator<T, ContanerIteratorType>(cells.end());
        }

        auto operator[](int index) {
            return MatrixE<DIM, decltype(std::make_tuple(index))>(*this, std::make_tuple(index));
        }

    private:
        ContanerType cells;
    };

    template<typename T, int DefVal, int Dim>
    Matrix<T, DefVal, Dim>::Matrix() {}

    template<typename T, int DefVal, int Dim>
    Matrix<T, DefVal, Dim>::~Matrix() {}
}