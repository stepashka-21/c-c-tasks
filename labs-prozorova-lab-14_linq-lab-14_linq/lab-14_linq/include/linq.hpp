#ifndef LINQ_H_
#define LINQ_H_

#include <utility>
#include <vector>
#include <iterator>

namespace linq {
    namespace impl {
        template<typename T, typename Iter>
        class range_enumerator;

        template<typename T>
        class drop_enumerator;

        template<typename T, typename U, typename F>
        class select_enumerator;

        template<typename T, typename F>
        class until_enumerator;

        template<typename T, typename F>
        class where_enumerator;

        template<typename T>
        class take_enumerator;

        template<typename T>
        class enumerator {
        public:
//            enumerator() = default;
//            virtual ~enumerator() = default;
            virtual const T& operator*() const = 0; // Получает текущий элемент.
            virtual enumerator& operator++() = 0;  // Переход к следующему элементу
            virtual explicit operator bool() const = 0;  // Возвращает true, если есть текущий элемент

            auto drop(int count) {
                return drop_enumerator<T>(*this, count);
            }

            auto take(int amount) {
                return take_enumerator<T>(*this, amount);
            }

            template<typename U = T, typename F>
            auto select(F&& func) {
                return select_enumerator<U, T, F>(*this, std::forward<F>(func));
            }

            template<typename F>
            auto until(F&& func) {
                return until_enumerator<T, F>(*this, std::forward<F>(func));
            }

            auto until_eq(const T& val) {
                return until([&val](const T& x) {
                    return x == val;
                });

            }

            template<typename F>
            auto where(F&& func) {
                return where_enumerator<T, F>(*this, std::forward<F>(func));
            }

            auto where_neq(const T& val) {
                return where([&val](const T& x) {
                    return x != val;
                });
            }

            std::vector<T> to_vector() {
                std::vector<T> vec;
                while (*this) {
                    vec.push_back(**this);
                    ++(*this);
                }
                return vec;
            }

            template<typename Iter>
            void copy_to(Iter it) {
                while (*this) {
                    *it = **this;
                    ++it;
                    ++(*this);
                }
            }
        };

        template<typename T, typename Iter>
        class range_enumerator : public enumerator<T> {
        public:
            range_enumerator(Iter begin, Iter end) : begin_(begin), end_(end) {}

            virtual enumerator<T>& operator++() {
                ++begin_;
                return *this;
            }

            virtual const T& operator*() const {
                return *begin_;
            }

            virtual explicit operator bool() const {
                return begin_ != end_;
            }

        private:
            Iter begin_, end_;
        };

        template<typename T>
        class drop_enumerator : public enumerator<T> {
        public:
            drop_enumerator(enumerator<T>& parent, int count) : parent_(parent), count_(count) {
                while (count_ > 0 && (bool) parent_) {
                    ++parent_;
                    --count_;
                }
            }

            virtual enumerator<T>& operator++() {
                ++parent_;
                return *this;
            }

            virtual const T& operator*() const {
                return *parent_;
            }

            virtual explicit operator bool() const {
                return (bool) parent_;
            }

        private:
            enumerator<T>& parent_;
            int count_;
        };

        template<typename T, typename U, typename F>
        class select_enumerator : public enumerator<T> {
        public:
            select_enumerator(enumerator<U> &parent, F&& func) : parent_(parent), func_(std::forward<F>(func)) {
                if ((bool) parent_) {
                    curr_ = func_(*parent_);
                }
            }

            virtual enumerator<T>& operator++() {
                ++parent_;
                if ((bool) parent_) {
                    curr_ = func_(*parent_);
                }
                return *this;
            }

            virtual const T& operator*() const {
                return curr_;
            }

            virtual explicit operator bool() const {
                return (bool) parent_;
            }

        private:
            enumerator<U>& parent_;
            F func_;
            T curr_;
        };

        template<typename T, typename F>
        class until_enumerator : public enumerator<T> {
        public:
            until_enumerator(enumerator<T>& parent, F&& predicate) : parent_(parent), predicate_(std::forward<F>(predicate)) {}

            virtual enumerator<T>& operator++() {
                if ((bool) parent_ && !predicate_(*parent_)) {
                    ++parent_;
                }
                return *this;
            }

            virtual const T& operator*() const {
                return *parent_;
            }

            virtual explicit operator bool() const {
                return (bool) parent_ && !predicate_(*parent_);
            }

        private:
            enumerator<T>& parent_;
            F predicate_;
        };

        template<typename T, typename F>
        class where_enumerator : public enumerator<T> {
        public:
            where_enumerator(enumerator<T> &parent, F&& func) : parent_(parent), func_(std::forward<F>(func)) {
                while ((bool) parent_ && !func_(*parent_)) {
                    ++parent_;
                }
            }

            virtual enumerator<T>& operator++() {
                ++parent_;
                while ((bool) parent_ && !func_(*parent_)) {
                    ++parent_;
                }
                return *this;
            }

            virtual const T& operator*() const {
                return *parent_;
            }

            virtual explicit operator bool() const {
                return (bool) parent_;
            }

        private:
            enumerator<T>& parent_;
            F func_;
        };

        template<typename T>
        class take_enumerator : public enumerator<T> {
        public:
            take_enumerator(enumerator<T> &parent, int count) : parent_(parent), count_(count) {}

            virtual enumerator<T>& operator++() {
                if (count_-- > 0)
                    ++parent_;
                return *this;
            }

            virtual const T& operator*() const {
                return *parent_;
            }

            virtual explicit operator bool() const {
                return count_ > 0 && (bool) parent_;
            }

        private:
            enumerator<T>& parent_;
            int count_ = 0;
        };
    } // namespace impl

    template<typename T>
    auto from(T begin, T end) {
        return impl::range_enumerator<typename std::iterator_traits<T>::value_type, T>(begin, end);
    }
} // namespace linq

#endif
